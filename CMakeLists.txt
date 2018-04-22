#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
set(CMAKE_MIN_VERSION 3.9.0)
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

#-------------------------------------------------------------------------------
# Output for all targets
#-------------------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#-------------------------------------------------------------------------------
# Project and Project dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# spdlog
#---------------------------------------
set(spd_log_include "spdlog/include/")
include_directories(${spd_log_include})

#---------------------------------------
# atb.common
#---------------------------------------
set(atb_common_target "atb.common")
include_directories(${atb_common_target}/include)
add_subdirectory(${atb_common_target})

#---------------------------------------
# atb.networking
#---------------------------------------
set(atb_networking_target "atb.networking")
add_subdirectory(${atb_networking_target})

#---------------------------------------
# atb.core
#---------------------------------------
set(atb_core_target "atb.core")
add_subdirectory(${atb_core_target})

#---------------------------------------
# atb
#---------------------------------------
set(atb_target "atb")
add_subdirectory(${atb_target})

#-------------------------------------------------------------------------------
# Build order
#-------------------------------------------------------------------------------
add_dependencies(${atb_core_target} ${atb_common_target})
add_dependencies(${atb_networking_target} ${atb_common_target})

add_dependencies(${atb_target} ${atb_networking_target})
