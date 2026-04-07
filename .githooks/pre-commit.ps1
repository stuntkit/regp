#!/usr/bin/env pwsh

Set-Location "$(git rev-parse --show-toplevel)" || exit 1

# load .venv
.\.venv\Scripts\activate.ps1
# load .\3rdparty\MSVC600\VC98\Bin\VCVARS32.ps1 
.\3rdparty\MSVC600\VC98\Bin\VCVARS32.ps1

# compile the project
if (Test-Path -Path "build") {
  # reconfigure cmake project
  cmake . -B build -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo
}

cmake --build build
cmake --build build

# run reccmp for all binaries
reccmp-reccmp --target STUNTGP --svg .\\status\\StuntGP.svg --html .\\status\\StuntGP.html --json .\\status\\StuntGP.json -T 803
reccmp-reccmp --target STUNTGP_D3D --svg .\\status\\StuntGP_D3D.svg --html .\\status\\StuntGP_D3D.html --json .\\status\\StuntGP_D3D.json -T 2259

if ($(git status --porcelain)) {
  git add status/
}
