#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_core "atb.core")

set(headers "")
set(sources "source/def.h"
            "source/example.cpp")

include_directories("include/")
include_directories("source/")
get_include_path(bin_include_path)

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
set(CMAKE_SKIP_RPATH ON)
add_library(${atb_core} SHARED ${sources} ${headers})
set_property(TARGET ${atb_core} PROPERTY POSITION_INDEPENDENT_CODE ON)

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Post build action
#-------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_core} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${bin_include_path}/${atb_core}
)