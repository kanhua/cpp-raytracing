cmake_minimum_required(VERSION 3.15)
project(cpp_raytracing)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(cpp_raytracing main.cpp OpticalRay.cpp OpticalRay.h AsphericSurface.cpp AsphericSurface.h)