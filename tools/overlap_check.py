#!/usr/bin/env python3
"""Report GLOBAL annotations whose original address ranges overlap.

Every `// GLOBAL: <TARGET> 0xADDR` annotation names a variable (the next code
line, or a `// name` comment line for library symbols). The variable's size is
taken from our build's PDB (GLOBALS + TYPES via cvdump), which gives the
original range [addr, addr + size). Two annotations whose ranges intersect mean
one of them is really a field/element of the other; reccmp then stops labelling
the original side, so they should be merged into one definition.

    PATH=~/.wine-regp/bin:$PATH .venv/bin/python tools/overlap_check.py \\
        --pdb build/StuntGP_D3D.pdb --src STUNTGP_D3D [--target STUNTGP_D3D] [-v]

Output: one line per problem, `INSIDE` (B lies wholly within A) or `OVERLAP`
(ranges cross), plus `DUP` for an address annotated twice. With -v it also lists
annotations whose symbol has no size in the PDB (not checked). The exit status
is 1 when any problem was found, so it can gate a commit.
"""
import argparse
import pathlib
import re
import sys

from reccmp.cvdump.runner import Cvdump
from reccmp.cvdump.types import CvdumpKeyError, CvdumpValueError

SOURCE_SUFFIXES = {".c", ".cpp", ".h", ".hpp"}
CODE_NAME = re.compile(r"([A-Za-z_][A-Za-z0-9_:]*)\s*(?:\[[^\]]*\]\s*)*(?:=|;|\{|$)")


def annotation_regex(target):
    return re.compile(r"//\s*GLOBAL:\s*" + re.escape(target) + r"\s+(0x[0-9A-Fa-f]+)")


def symbol_name(lines, i):
    """Name of the variable annotated at line i: the first following line that
    is not another annotation. A comment line (`// ___argc`) names a library
    symbol that has no definition in our source."""
    for line in lines[i + 1 :]:
        s = line.strip()
        if not s or re.match(r"//\s*[A-Z]+:", s):
            continue
        if s.startswith("//"):
            return s[2:].strip()
        m = CODE_NAME.search(s.split("=")[0].rstrip() + ";")
        return m.group(1) if m else None
    return None


def read_annotations(src, target):
    """[(addr, name, 'file:line')] for every GLOBAL annotation under src."""
    regex = annotation_regex(target)
    out = []
    for path in sorted(pathlib.Path(src).rglob("*")):
        if path.suffix.lower() not in SOURCE_SUFFIXES:
            continue
        lines = path.read_text(encoding="latin-1").splitlines()
        for i, line in enumerate(lines):
            m = regex.search(line)
            if m:
                out.append((int(m.group(1), 16), symbol_name(lines, i), f"{path}:{i + 1}"))
    return out


def read_sizes(pdb):
    """{name: size} for every S_GDATA32/S_LDATA32 symbol in the PDB. Names that
    occur more than once (file statics) keep their largest size."""
    parser = Cvdump(pdb).globals().types().run()
    sizes = {}
    for g in parser.globals:
        try:
            size = parser.types.get(g.type).size
        except (CvdumpKeyError, CvdumpValueError):
            size = None
        if size:
            sizes[g.name] = max(size, sizes.get(g.name, 0))
    return sizes


def lookup(sizes, name):
    # C symbols appear with or without the leading underscore depending on how
    # they were declared; annotations use the decorated (public) form.
    for cand in (name, name[1:] if name.startswith("_") else None, "_" + name):
        if cand and cand in sizes:
            return sizes[cand]
    return None


def find_problems(items):
    """items: sorted [(addr, size, name, where)]. Yields (kind, a, b)."""
    for i, a in enumerate(items):
        a_end = a[0] + a[1]
        for b in items[i + 1 :]:
            if b[0] >= a_end:
                break
            if b[0] == a[0]:
                yield "DUP", a, b
            elif b[0] + b[1] <= a_end:
                yield "INSIDE", a, b
            else:
                yield "OVERLAP", a, b


def fmt(item):
    addr, size, name, where = item
    return f"{name} 0x{addr:x}+0x{size:x} ({where})"


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--pdb", required=True, help="our build's PDB")
    ap.add_argument("--src", required=True, help="source tree to scan for annotations")
    ap.add_argument("--target", default="STUNTGP_D3D", help="annotation target name")
    ap.add_argument("-v", "--verbose", action="store_true", help="also list unsized symbols")
    args = ap.parse_args()

    sizes = read_sizes(args.pdb)
    items, unsized = [], []
    for addr, name, where in read_annotations(args.src, args.target):
        size = lookup(sizes, name) if name else None
        if size is None:
            unsized.append((addr, name, where))
            size = 1  # still catches duplicate addresses and lands inside others
        items.append((addr, size, name, where))
    items.sort(key=lambda t: (t[0], -t[1]))

    problems = list(find_problems(items))
    for kind, a, b in problems:
        rel = b[0] - a[0]
        print(f"{kind:8} {fmt(b)} at +0x{rel:x} of {fmt(a)}")
    if args.verbose:
        for addr, name, where in unsized:
            print(f"UNSIZED  {name} 0x{addr:x} ({where})")
    print(f"{len(items)} annotations, {len(unsized)} without PDB size, {len(problems)} problems",
          file=sys.stderr)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
