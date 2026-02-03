## Hoshen Kopelman Algorithm
----
Module for python

## Requirements

- Linux / WSL
- CMake >= 3.21
- C++17 compatible compiler (g++)
- Python >= 3.10
- vcpkg

## Quick start

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  ninja-build \
  cmake \
  pkg-config \
  python3-dev \
  python3-pip

git clone https://github.com/username/HoshenKopelmanLattice.git
cd HoshenKopelmanLattice

git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
export VCPKG_ROOT=~/vcpkg

cmake --preset release
cmake --build build/release
