#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_common_target "atb.common")

set(headers "include/ip_address_v4.h"
            "include/network_message.h"
            "include/thread_safe_queue.h")
set(sources "source/example.cpp")

add_library(${atb_common_target} SHARED ${sources} ${headers})