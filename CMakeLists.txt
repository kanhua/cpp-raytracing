cmake_minimum_required(VERSION 3.15)
project(cpp_raytracing)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("./googletest")
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIR})

add_executable(cpp_raytracing main.cpp OpticalRay.cpp OpticalRay.h AsphericSurface.cpp AsphericSurface.h)

add_executable(test_newton tests/test_newton.cpp)
target_link_libraries(test_newton gtest_main)