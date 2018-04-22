#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_target "atb")

set(headers "")
set(sources "main.cpp")
include_directories(${atb_library_include_path})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                             atb                            -")
message(STATUS "--------------------------------------------------------------")

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
project(${atb_target})
set(CMAKE_SKIP_RPATH ON)
add_executable(${atb_target} ${sources} ${headers})

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# boost
#---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost include dir:   "      ${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost Libraries dir: "    ${Boost_LIBRARIES})

#---------------------------------------
# atb.networking
#---------------------------------------
get_platform_independent_static_library_name(atb_networking_library "atb.networking")

set(atb_networking_library ${atb_library_binary_path}/${atb_networking_library})
message(STATUS "atb -> Networking library:  " ${atb_networking_library})

#---------------------------------------
# set libraries
#---------------------------------------
target_link_libraries(${atb_target} ${atb_networking_library} ${Boost_LIBRARIES})

#---------------------------------------
# atb.common
#---------------------------------------
