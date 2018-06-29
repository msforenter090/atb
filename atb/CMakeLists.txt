# ------------------------------------------------------------------------------
# General
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_target "atb")

set(headers "")
set(sources "main.cpp")
include_directories(${atb_library_include_path})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                             atb                            -")
message(STATUS "--------------------------------------------------------------")

# ------------------------------------------------------------------------------
# Compiler options and target
# ------------------------------------------------------------------------------
project(${atb_target})
set(CMAKE_SKIP_RPATH ON)
add_executable(${atb_target} ${sources} ${headers})

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# --------------------------------------
# atb.common
# --------------------------------------
get_platform_independent_static_library_name(atb_common_library "atb.common")
set(atb_common_library ${atb_library_binary_path}/${atb_common_library})
include_directories(${atb_library_include_path}/${atb_common_target})
message(STATUS "atb -> atb.common library:  " ${atb_common_library})

# ---------------------------------------
# atb.networking
# ---------------------------------------
get_platform_independent_static_library_name(atb_networking_library "atb.networking")
set(atb_networking_library ${atb_library_binary_path}/${atb_networking_library})
include_directories(${atb_library_include_path})
message(STATUS "atb -> Networking library:  " ${atb_networking_library})

# ---------------------------------------
# boost
# ---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost include dir:   "      ${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost Libraries dir: "    ${Boost_LIBRARIES})

# ---------------------------------------
# set libraries
# ---------------------------------------
target_link_libraries(${atb_target} ${atb_networking_library} ${atb_common_library} ${Boost_LIBRARIES})
