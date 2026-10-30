# How to contribute

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
1. `cmake . -B build -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
   - You can also use `DCMAKE_BUILD_TYPE` of `RelWithDebInfo`/`Release`/`Debug`
1. `cmake --build build` - run it twice, as some things get compiled/referenced/whatever only on the second run (TODO: check if still valid with cmake build instead of manul nmake).

### Compiling with a modern compiler

1. Open your favourite command prompt, `cmd` , ~~or `PowerShell` will do~~.
1. Run ~~`& 'C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars32.bat'` in pwsh or~~ `"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars32.bat"` in cmd.
1. Create `build_modern` directory if it doesn't exists already.
1. `cd` to the build directory.
1. `cmake . -B build_modern -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
   - You can also use `DCMAKE_BUILD_TYPE` of `RelWithDebInfo`/`Release`/`Debug`
1. `cmake --build build`

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

## Creating code

I don't yet have a very strict set of rules, but here they are:

- use `clang-format`, there's a config file in the root directory that describes the basic format of the C++ files.
- initialize variables in a `= {}` manner (copy list initialization, or default init where applicable).

### Nice to have, for the future expansion

- make sure TCHAR is used everywhere, the Polish version was compiled with UNICODE support, so the code was possibly written to support that by simply specyfying compilation flags.
