# ReGP

Stunt GP decompilation project, loosely based on the [LEGO Island Decompilation](https://github.com/isledecomp/isle).

## Status

<!--<img src="./status/config.svg" alt="config" width="33%"/>-->
<!--<img src="./status/StuntGP.svg" alt="StuntGP" width="33%"/>-->
<img src="./status/StuntGP_D3D.svg" alt="StuntGP_D3D" width="50%"/>
<!--<img src="./status/StuntGP_GLIDE.svg" alt="StuntGP_GLIDE" width="50%"/>-->

## Usage

There is no working binary.

In theory, when enough work is done, you could just put the compiled executables in the game directory and run them. In practice almost nothing works yet.

## What's working

- Fullscreen window gets created, no DirectX surface yet

## What's broken

- WAD file support is just a few stub functions
- everything else

## Building and contributing

If you wish to build the project yourself, or to contribute to it, please see the ["How to contribute" guide](./CONTRIBUTING.md).

## Used version

This decompilation is based on the international PC version of the game with the following files and their sha256 checksums:

| Filename            | SHA                                                                |
| ------------------- | ------------------------------------------------------------------ |
| `config.exe`        | `9c234da54a05392455a44b2d38482eefd303fd200a75c8703e32074989486214` |
| `StuntGP.exe`       | `e4d2c2641c0028c6106de0e18d23ebd305d9af08fda4fbcc891540e92a1207a9` |
| `StuntGP_D3D.exe`   | `4a1d234ce1f095a427bb7f2f0174294b8c85a8fdbbc29b62a3863156b2f16a1b` |
| `StuntGP_Glide.exe` | `2c1513cb0438180db0099850d5a449afe1ac5658c89348e49bb952386a872655` |
