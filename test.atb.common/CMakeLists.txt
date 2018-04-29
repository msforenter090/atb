#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_common_test_target "test.atb.common")

set(headers "")
set(sources "source/main.cpp")
include_directories(${atb_library_include_path})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                             atb                            -")
message(STATUS "--------------------------------------------------------------")

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
project(${atb_common_test_target})
set(CMAKE_SKIP_RPATH ON)
add_executable(${atb_common_test_target} ${sources} ${headers})
