# ReGP

Stunt GP decompilation project, loosely based on the [LEGO Island Decompilation](https://github.com/isledecomp/isle).

## Used version

This decompilation is based on the international PC version of the game with the following files and their sha256 checksums:

```plain
9c234da54a05392455a44b2d38482eefd303fd200a75c8703e32074989486214  config.exe
4a1d234ce1f095a427bb7f2f0174294b8c85a8fdbbc29b62a3863156b2f16a1b  StuntGP_D3D.exe
e4d2c2641c0028c6106de0e18d23ebd305d9af08fda4fbcc891540e92a1207a9  StuntGP.exe
2c1513cb0438180db0099850d5a449afe1ac5658c89348e49bb952386a872655  StuntGP_Glide.exe

```

## Status

Only compilation of a dummy main.cpp through MSVC 6 works.

## Building

For now, the code is only checked and compiled against MSVC 6.0, like in the original game.

### Prerequisites

You'll need:

- CMake
- Microsoft Visual C++ 6.0. [portable ver](https://github.com/halamix2/MSVC600/tree/6.00.8168)
  - the portable version with the PowerShell support was added as a git submodule. You can download it by issuing the `git submodule update --init --recursive` command.
- DirectX 6 SDK, a copy is included in the 3rdparty directory.

Nice to have:

- Compilation should always work under both CMD and PowerShell, but the primary command line I've used for the development is PowerShell 7.

### Compiling

1. Open your favourite command prompt, `cmd` , or `PowerShell` will do.
1. From the `MSVC600` directory, run `VC98\Bin\VCVars32.BAT`, or `VC98\Bin\VCVARS32.ps1`, depending on your command prompt, to set enviroment variables necessary for compilation.
1. Create `build` directory if it doesn't exists already.
1. `cd` to the build directory.
1. `cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
    - You can also use `DCMAKE_BUILD_TYPE` of `RelWithDebInfo`/`Release`/`Debug`
1. `nmake` - run it twice, as some things get compiled/referenced/whatever only on the second run.

## Comparison

For comparison with the original files we're using the [reccmp](https://github.com/isledecomp/reccmp) project:

1. Create `originals` directory
1. Copy your original .exxe file(s) to the `originals` directory
1. Create Python virtual env (once): `python -m venv .venv`
1. Enable venv: `.\.venv\Scripts\activate.ps1` (or`.bat` if you're using CMD)
1. Install dependencies (once): `pip install -r .\tools\requirements.txt`
1. Update local reccmp user config: `reccmp-project detect --search-path originals`
1. `cd` to directory with build exe files
1. Update local reccmp build config: `reccmp-project detect --what recompiled --search-path build`
1. Compare original and recomp: `reccmp-reccmp --target STUNTGP_D3D`

## Usage

In theory when enough work is done you could just put the compiled executables in the game directory and run them. Currently this is a very bad ise, as nothing works (yet).
