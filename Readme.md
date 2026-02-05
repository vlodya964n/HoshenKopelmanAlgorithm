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
```
## Google Colab

```bash
!apt update
!apt install -y \
  build-essential \
  cmake \
  pkg-config

!pip install pybind11

!git clone https://github.com/vlodya964n/HoshenKopelmanAlgorithm.git
%cd HoshenKopelmanAlgorithm

!python3 -m pybind11 --cmakedir

!cmake -B build -S . \
  -Dpybind11_DIR=$(python3 -m pybind11 --cmakedir) \
  -DCMAKE_BUILD_TYPE=Release

!cmake --build build -j

!ls build/*.so

import sys
sys.path.append("build")

import hoshen_kopelman_lattice
print(hoshen_kopelman_lattice)
```
