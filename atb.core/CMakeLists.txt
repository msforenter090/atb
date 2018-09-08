# ------------------------------------------------------------------------------
# General
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                          atb.core                          -")
message(STATUS "--------------------------------------------------------------")

set(atb_core "atb.core")

set(headers "include/atb_settings_loader.h"
            "include/atb_settings.h"
            "include/pipeline.h"
            "include/zone.h")
set(sources "source/atb_settings_loader.cpp"
            "source/atb_settings.cpp"
            "source/mode_handler.h"
            "source/mode_sync.h"
            "source/mode_sync.cpp"
            "source/mode_wo.h"
            "source/mode_wo.cpp"
            "source/pipeline.cpp"
            "source/zone.cpp")

include_directories("include")
include_directories("source")
get_include_path(bin_include_path)

# ------------------------------------------------------------------------------
# target setup
# ------------------------------------------------------------------------------
add_library(${atb_core} STATIC ${sources} ${headers})
set_property(TARGET ${atb_core} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# --------------------------------------
# atb.common
#---------------------------------------
include_directories(${atb_library_include_path})

# --------------------------------------
# boost
# --------------------------------------
include_directories(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# Post build action
# ------------------------------------------------------------------------------
add_custom_command(TARGET ${atb_core} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${bin_include_path}/${atb_core}
)

