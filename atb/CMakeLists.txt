#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_target "atb")

set(headers "")
set(sources "main.cpp")

project(${atb_target})
add_executable(${atb_target} ${sources} ${headers})