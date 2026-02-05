cmake_minimum_required(VERSION 3.15)
project(hoshen_kopelman_lattice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(pybind11 CONFIG REQUIRED)

set(SOURCES
    src/hoshen_kopelman_lattice.cpp
    src/utils.h
    src/ObjectsSystem/Objects.h
    src/ObjectsSystem/Objects.cpp
    src/ClustersCalculate/clusters_calculate.h
    src/ClustersCalculate/clusters_calculate.cpp
    src/PercolationSystem/percolation_system.h
    src/PercolationSystem/percolation_system.cpp
    src/ComputePercolation/compute_percolation.h
    src/ComputePercolation/compute_percolation.cpp
)

pybind11_add_module(hoshen_kopelman_lattice ${SOURCES})

target_link_libraries(hoshen_kopelman_lattice PRIVATE stdc++)
