cmake_minimum_required(VERSION 3.10)
project(HVM VERSION 2.0.18 LANGUAGES C)

# Preliminary Checks ###########################################################
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# Fixed Options ################################################################
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Code #########################################################################
add_subdirectory(src)
add_subdirectory(wgl)
