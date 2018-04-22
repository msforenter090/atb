#-------------------------------------------------------------------------------
# Useful:
# https://unix.stackexchange.com/questions/89211/how-to-test-whether-a-linux-binary-was-compiled-as-position-independent-code
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_networking_target "atb.networking")

set(headers "include/network_junction.h")
set(sources "source/network_client.h"
            "source/network_client.cpp"
            "source/network_junction.cpp")

include_directories("include/")
include_directories("source/")

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                       atb.networking                       -")
message(STATUS "--------------------------------------------------------------")

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
set(CMAKE_SKIP_RPATH ON)
add_library(${atb_networking_target} STATIC ${sources} ${headers})
set_property(TARGET ${atb_networking_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# boost
#---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${atb_networking_target} ${Boost_LIBRARIES})
message(STATUS "atb.networking -> Boost include dir:    " ${Boost_INCLUDE_DIRS})
message(STATUS "atb.networking -> Boost Libraries dir:  " ${Boost_LIBRARIES})

#-------------------------------------------------------------------------------
# Post build action
#-------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_networking_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${atb_library_include_path}/${atb_networking_target}
)
