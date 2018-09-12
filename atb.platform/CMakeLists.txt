# ------------------------------------------------------------------------------
# Useful:
# https://unix.stackexchange.com/questions/89211/how-to-test-whether-a-linux-binary-was-compiled-as-position-independent-code
# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# General
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                        atb.platform                        -")
message(STATUS "--------------------------------------------------------------")

set(atb_platform_target "atb.platform")

set(headers "include/platform.h"
            "include/daemonizer.h")
set(sources "source/daemonizer.cpp")

include_directories("include/")
include_directories("source/")

# ------------------------------------------------------------------------------
# target setup
# ------------------------------------------------------------------------------
add_library(${atb_platform_target} STATIC ${sources} ${headers})
set_property(TARGET ${atb_platform_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ------------------------------------------------------------------------------
# Post build action
# ------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_platform_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${atb_library_include_path}/${atb_platform_target}
)

