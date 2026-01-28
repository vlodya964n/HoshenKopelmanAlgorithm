cmake_minimum_required(VERSION 3.15)
project(hoshen_kopelman_lattice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

set(SOURCES
    src/hoshen_kopelman_lattice.cpp
    src/alghoritm.h
)

pybind11_add_module(hoshen_kopelman_lattice ${SOURCES})

target_link_libraries(hoshen_kopelman_lattice PRIVATE stdc++)
target_link_libraries(hoshen_kopelman_lattice PRIVATE Eigen3::Eigen)
