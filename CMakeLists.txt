cmake_minimum_required(VERSION 3.9)

project(ULLib)

set(BUILD_SAMPLES CACHE FALSE BOOL "Build examples")

add_subdirectory(ULLib)

if(BUILD_SAMPLES)
    add_subdirectory(Samples)
endif(BUILD_SAMPLES)
