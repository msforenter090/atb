#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_core "atb.core")

set(headers "include/def.h")
set(sources "source/example.cpp")

add_library(${atb_core} SHARED ${sources} ${headers})

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
