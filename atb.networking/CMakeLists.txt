# ------------------------------------------------------------------------------
# Useful:
# https://unix.stackexchange.com/questions/89211/how-to-test-whether-a-linux-binary-was-compiled-as-position-independent-code
# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# General
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                       atb.networking                       -")
message(STATUS "--------------------------------------------------------------")

set(atb_networking_target "atb.networking")

set(headers "include/read_callback.h"
            "include/network_junction.h")
set(sources "source/network_client.h"
            "source/network_client.cpp"
            "source/network_junction.cpp")

include_directories("include/")
include_directories("source/")

# ------------------------------------------------------------------------------
# target setup
# ------------------------------------------------------------------------------
add_library(${atb_networking_target} STATIC ${sources} ${headers})
set_property(TARGET ${atb_networking_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# --------------------------------------
# atb.common
# --------------------------------------
include_directories(${atb_library_include_path})

# --------------------------------------
# boost
# --------------------------------------
include_directories(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Post build action
# ------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_networking_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${atb_library_include_path}/${atb_networking_target}
)

