#!/usr/bin/env python3
"""Find statically linked CRT (LIBC.lib) functions of our build in the original exe.

For every public symbol in a LIBC module's .text contribution of our PDB, take its
bytes from our exe, mask relocatable operands (rel32 call/jmp, Jcc leaving the
function, 4-byte absolute addresses, jump-table entries), and regex-search the
original's CRT region. A whole contribution is tried first, which pins tiny or
duplicated functions by their neighbours. Only unique hits are reported as matches.

    PATH=~/.wine-regp/bin:$PATH .venv/bin/python tools/crt_match.py \\
        --orig originals/game/Program_Executable_Files/StuntGP_D3D.exe \\
        --exe build/StuntGP_D3D.exe --pdb build/StuntGP_D3D.pdb \\
        --header STUNTGP_D3D/library_msvc.h [--ghidra callgraph.jsonl] [--apply]

Without --apply it prints a TSV: status, name(s), our addr, size, original hit(s),
obj, label state. With --apply it adds `// LIBRARY: STUNTGP_D3D` lines for unique
matches plus RESOLVED. Verify new labels with reccmp afterwards: a 0% score means
a wrong name or address.
"""
import argparse
import bisect
import json
import re
import struct
import subprocess

import capstone
from reccmp.cvdump.runner import Cvdump

CRT_START = 0x4627a0
IMG_LO, IMG_HI = 0x400000, 0x700000

# Ambiguous byte matches resolved by hand (identical code, or too short to search).
RESOLVED = {
    "__fpclear": 0x4627D3,  # 1-byte ret between __fpmath and __cfltcvt_init
    "__matherr": 0x46BC78,  # xor eax,eax; ret; called from __umatherr
    "__ld12tod": 0x46AE9D,  # called by __atodbl and __fltin
    "__ld12tof": 0x46AEB3,  # called by __atoflt
    "__atodbl": 0x46AEC9,
    "__atoflt": 0x46AEF6,
    "_memmove": 0x46B120,  # _memcpy (0x4692b0) is the copy called from _fread
}
# Both names sit on one address; reccmp pairs by this one.
PREFER = {"__alloca_probe": "__chkstk", "__stricmp": "__strcmpi"}


def text_section(path):
    d = open(path, "rb").read()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    nsec, opt = struct.unpack_from("<H", d, pe + 6)[0], struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<I", d, pe + 52)[0]
    for i in range(nsec):
        name, vs, va, _, ro = struct.unpack_from("<8sIIII", d, pe + 24 + opt + 40 * i)
        if name.rstrip(b"\0") == b".text":
            return base + va, d[ro : ro + vs]
    raise SystemExit("no .text in " + path)


def read_pdb(pdb):
    """Modules, .text publics and .text section contributions from cvdump."""
    cmd = Cvdump(pdb).publics().modules().section_contributions().cmd_line()
    out = subprocess.run(cmd, capture_output=True).stdout.decode("utf-8", "ignore")
    mods, pubs, contribs, sec = {}, {}, [], None
    for line in out.splitlines():
        if line.startswith("*** "):
            sec = line[4:].strip()
        elif sec == "MODULES" and (m := re.match(r'([0-9A-F]{4}) "(.*?)"(?: "(.*?)")?', line)):
            mods[int(m[1], 16)] = (m[2], m[3] or "")
        elif sec == "PUBLICS" and (m := re.match(r"S_PUB32: \[0001:([0-9A-F]+)\], Flags: \w+, (\S+)", line)):
            pubs.setdefault(int(m[1], 16), []).append(m[2])
        elif sec == "SECTION CONTRIBUTIONS" and (m := re.match(r"\s+([0-9A-F]{4})\s+0001:([0-9A-F]+)\s+([0-9A-F]+)", line)):
            contribs.append((int(m[1], 16), int(m[2], 16), int(m[3], 16)))
    return mods, pubs, contribs


def pattern(code, va):
    """Regex for code at va with relocatable bytes wildcarded."""
    mask = [False] * len(code)
    end = va + len(code)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    off = 0
    while off < len(code):
        insn = next(md.disasm(code[off:], va + off, 1), None)
        if insn is None:
            off += 1
            continue
        b = insn.bytes
        if b[0] in (0xE8, 0xE9) and insn.size == 5:
            mask[off + 1 : off + 5] = [True] * 4
        elif b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and insn.size == 6:
            tgt = (insn.address + 6 + struct.unpack_from("<i", b, 2)[0]) & 0xFFFFFFFF
            if not va <= tgt < end:
                mask[off + 2 : off + 6] = [True] * 4
        for fo, fs in ((insn.disp_offset, insn.disp_size), (insn.imm_offset, insn.imm_size)):
            if fo and fs == 4 and IMG_LO <= struct.unpack_from("<I", b, fo)[0] < IMG_HI:
                mask[off + fo : off + fo + 4] = [True] * 4
        off += insn.size
    # switch jump tables live inside the function and need not be aligned
    for k in range(len(code) - 3):
        if va <= struct.unpack_from("<I", code, k)[0] < end:
            mask[k : k + 4] = [True] * 4
    return re.compile(b"".join(b"." if m else re.escape(code[k : k + 1]) for k, m in enumerate(mask)), re.DOTALL)


def strip_padding(code):
    n = len(code)
    while n > 1 and code[n - 1] in (0xCC, 0x90):
        n -= 1
    return code[:n]


def header_labels(lines):
    labels = {}
    for i, line in enumerate(lines):
        if m := re.match(r"// LIBRARY: STUNTGP_D3D (0x[0-9a-fA-F]+)", line):
            j = i + 1
            while lines[j].startswith("// LIBRARY:"):
                j += 1
            labels[lines[j][3:].strip()] = int(m[1], 16)
    return labels


def match(args):
    mods, pubs, contribs = read_pdb(args.pdb)
    our_va, our_text = text_section(args.exe)
    org_va, org_text = text_section(args.orig)
    crt = org_text[CRT_START - org_va :]
    libc = {i for i, (lib, _) in mods.items() if lib.upper().endswith("LIBC.LIB")}
    offs = sorted(pubs)

    def search(code, va):
        return [CRT_START + m.start() for m in pattern(code, va).finditer(crt)]

    results = []
    for mod, coff, csize in contribs:
        if mod not in libc:
            continue
        fns = offs[bisect.bisect_left(offs, coff) : bisect.bisect_left(offs, coff + csize)]
        obj = mods[mod][1].split("\\")[-1]
        whole = strip_padding(our_text[coff : coff + csize])
        whole_hits = search(whole, our_va + coff) if len(whole) >= 16 else []
        for n, fo in enumerate(fns):
            fe = fns[n + 1] if n + 1 < len(fns) else coff + csize
            if len(whole_hits) == 1:
                st, hits = "unique", [whole_hits[0] + fo - coff]
            else:
                code = strip_padding(our_text[fo:fe])
                if len(code) < 6:
                    st, hits = "short", []
                else:
                    hits = search(code, our_va + fo)
                    st = {0: "none", 1: "unique"}.get(len(hits), "multi")
            results.append((st, pubs[fo], our_va + fo, fe - fo, hits, obj))
    return results


def apply(lines, new):
    tail = []
    for name, addr in new:
        tag = "// LIBRARY: STUNTGP_D3D 0x%x" % addr
        if ("// " + name) not in lines:
            tail += [tag, "// " + name, ""]
            continue
        i = lines.index("// " + name)
        j = i - 1
        while j >= 0 and re.match(r"// (LIBRARY|GLOBAL): ", lines[j]):
            if lines[j].startswith("// GLOBAL: STUNTGP_D3D"):  # function mislabelled as data
                lines[j] = tag
                break
            j -= 1
        else:
            lines.insert(i, tag)
    end = max(i for i, l in enumerate(lines) if l.strip() == "#endif")
    lines[end:end] = tail


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    p.add_argument("--orig", required=True)
    p.add_argument("--exe", required=True)
    p.add_argument("--pdb", required=True)
    p.add_argument("--header", required=True)
    p.add_argument("--ghidra", help="callgraph.jsonl; lists original CRT functions left unmatched")
    p.add_argument("--apply", action="store_true")
    args = p.parse_args()

    lines = open(args.header).read().split("\n")
    labels = header_labels(lines)
    results = match(args)
    new = []
    for st, names, va, size, hits, obj in results:
        name = PREFER.get(names[0], names[0])
        state = ""
        if name in labels:
            state = "labelled" if labels[name] in hits or labels[name] == RESOLVED.get(name) else "LABEL_MISMATCH"
        elif name in RESOLVED:
            new.append((name, RESOLVED[name]))
            state = "resolved"
        elif st == "unique":
            new.append((name, hits[0]))
            state = "new"
        print("\t".join([st, "|".join(names), "%x" % va, str(size), ",".join("%x" % h for h in hits[:6]), obj, state]))

    if args.ghidra:
        found = {h for r in results if r[0] == "unique" for h in r[4]} | set(labels.values()) | {a for _, a in new}
        for line in open(args.ghidra):
            e = json.loads(line)
            if e["entry"] >= CRT_START and e["entry"] not in found:
                print("#unmatched\t%x\t%s\t%d" % (e["entry"], e["name"], e["size"]))

    if args.apply and new:
        apply(lines, new)
        open(args.header, "w").write("\n".join(lines))
    print("# %d new labels%s" % (len(new), " written" if args.apply else ""))


if __name__ == "__main__":
    main()
