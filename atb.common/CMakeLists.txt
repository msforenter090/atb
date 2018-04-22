#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_common_target "atb.common")

set(headers "include/ip_address_v4.h"
            "include/network_message.h"
            "include/thread_safe_queue.h")
set(sources "source/example.cpp")

include_directories("include/")
include_directories("source/")
get_include_path(bin_include_path)

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
set(CMAKE_SKIP_RPATH ON)
add_library(${atb_common_target} SHARED ${sources} ${headers})
set_property(TARGET ${atb_common_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

#-------------------------------------------------------------------------------
# Post build action
#-------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_common_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${bin_include_path}/${atb_common_target}
)