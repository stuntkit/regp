# ReGP

Stunt GP decompilation project, loosely based on the [LEGO Island Decompilation](https://github.com/isledecomp/isle).

## Used version

This decompilation is based on the international PC version of the game with the following files and their MD5 checksums:

```plain
4ae3d80318f1acda0e530f0281a27b05  config.exe
e4baf3e5cacd51afce61007f72781167  StuntGP_D3D.exe
95848b088f0b72248525de45f44b29f1  StuntGP.exe
c5801f89e46c53a67ac8d7c18a94acd8  StuntGP_Glide.exe
```

## Status

Only compilation of a dummy main.cpp through MSVC 6 works.

## Building

For now, the code is only checked and compiled against MSVC 6.0, like in the original game.

### Prerequisites

You'll need:

- CMake
- Microsoft Visual C++ 6.0. [portable ver](https://github.com/itsmattkc/MSVC600)
  - put in a directory without any spaces in path just in case
  - `checkout 17bae53fa330df7b576f25f1f604e4214076a650 commit`
  - a [fork](https://github.com/halamix2/MSVC600/tree/6.00.8168) with thePowerShell support is added as a git submodule. You can download it by issuing the `git submodule update --init --recursive` command
- ~~DirectX 6 SDK~~, a copy is icluded in 3rdparty directory

Nice to have:

- Compilation should always work under both CMD and PowerShell, but the primary command line for the development is PowerShell 7.

### Compiling

1. Open your favourite command prompt, `cmd` , or `PowerShell` will do.
1. From the `MSVC600` directory, run `VC98\Bin\VCVars32.BAT`, or `VC98\Bin\VCVARS32.ps1`, depending on your command prompt, to set enviroment variables necessary for compilation.
1. Create `build` directory if it doesn't exists already.
1. `cd` to the build directory.
1. `cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
    - You can also use `DCMAKE_BUILD_TYPE` of `RelWithDebInfo`/`Release`/`Debug`
1. `nmake` - run it twice, as some things get compiled/referenced/whatever only on the second run.

## Usage

In theory when enough work is done you could just put the compiled executables in the game directory and run them. Currently this is a very bad ise, as nothing works (yet).

## TODO

Stuff still waiting:

- automate loading .exe, .pdb & doing autoanalysis in Ghidra on the regp.exe
