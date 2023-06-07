cmake_minimum_required(VERSION 3.16.0)
project(hash_table VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLE "Build example code" OFF)
option(BUILD_PYTHON_BINDINGS "Build python bindings for scripting" OFF)

add_subdirectory(hash_table)
if (BUILD_PYTHON_BINDINGS)
    add_subdirectory(scripts)
endif()
if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
