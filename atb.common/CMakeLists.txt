#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                         atb.common                         -")
message(STATUS "--------------------------------------------------------------")

set(atb_common_target "atb.common")

set(headers "include/def.h"
            "include/logger.h"
            "include/ip_address_v4.h"
            "include/network_message.h"
            "include/thread_safe_queue.h"
            "include/message_correction_machine.h")
set(sources "source/message_correction_machine.cpp")

include_directories("include/")
include_directories("source/")
get_include_path(bin_include_path)

add_definitions(-DATB_COMMON_API_EXPORT)

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
set(CMAKE_SKIP_RPATH ON)
add_library(${atb_common_target} STATIC ${sources} ${headers})
set_property(TARGET ${atb_common_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# boost
#---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${atb_common_target} ${Boost_LIBRARIES})
message(STATUS "atb.common -> Boost include dir:    " ${Boost_INCLUDE_DIRS})
message(STATUS "atb.common -> Boost Libraries dir:  " ${Boost_LIBRARIES})

#-------------------------------------------------------------------------------
# Post build action
#-------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_common_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${bin_include_path}/${atb_common_target}
)
