cmake_minimum_required(VERSION 3.10)  #default CLion uses Version 3.15
project(cpp_raytracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_subdirectory("googletest/")
#add_subdirectory("abseil-cpp/")

#set(yaml-cpp_DIR /home/kanhua/Documents/yaml-cpp/build)
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PLPLOT REQUIRED plplot-c++)

add_definitions(${yaml-cpp_DEFINITIONS})

include_directories(${Boost_INCLUDE_DIRS} ${yaml-cpp_INCLUDE_DIRS} ${PLPLOT_INCLUDE_DIRS} "./" "eigen/")

#link_directories(${Boost_LIBRARY_DIR})
#link_directories(${yaml-cpp_LIBRARY_DIRS})

set(RAY_TRACING_SRC OpticalRay.cpp AsphericSurface.cpp OpticalSystem.cpp)

set(HELPER_LIB yaml-cpp ${PLPLOT_LIBRARIES})

message( ${PLPLOT_LIBRARIES} )
#message( ${yaml_cpp_LIBRARIES} )

add_library(main_lib ${RAY_TRACING_SRC})
target_link_libraries(main_lib yaml-cpp ${PLPLOT_LIBRARIES})

add_executable(cpp_raytracing main.cpp)
target_link_libraries(cpp_raytracing main_lib)

add_executable(test_newton tests/test_newton.cpp)
target_link_libraries(test_newton gtest_main)

add_executable(test_plplot tests/plc++demos.h tests/test_plplot.cpp)
target_link_libraries(test_plplot ${HELPER_LIB})

add_executable(test_aspheric_surface tests/test_aspheric_surface.cpp)
target_link_libraries(test_aspheric_surface gtest_main ${HELPER_LIB} main_lib)

add_executable(test_plplot_uniqueptr tests/plc++demos.h tests/test_plplot_unique_ptr.cpp)
target_link_libraries(test_plplot_uniqueptr ${PLPLOT_LIBRARIES})

add_executable(test_plplot_helper tests/test_plplot_helper.cpp)
target_link_libraries(test_plplot_helper ${PLPLOT_LIBRARIES} gtest_main)

add_executable(test_yaml tests/test_yaml.cpp)
target_link_libraries(test_yaml yaml-cpp gtest_main ${HELPER_LIB} main_lib)
