cmake_minimum_required(VERSION 3.9)
project(tsp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
add_executable(tsp main.cpp tsp.cpp tsp.h tester.cpp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(tsp PUBLIC OpenMP::OpenMP_CXX)
endif()