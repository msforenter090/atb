# ------------------------------------------------------------------------------
# General
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                             atb                            -")
message(STATUS "--------------------------------------------------------------")

set(atb_target "atb")

set(headers "include/application.h"
            "include/logger_callback.h"
            "include/logger_hub.h")
set(sources "source/application.cpp"
            "source/logger_hub.cpp"
            "source/main.cpp")
include_directories(${atb_library_include_path})
include_directories("include/")

# ------------------------------------------------------------------------------
# target setup
# ------------------------------------------------------------------------------
project(${atb_target})
add_executable(${atb_target} ${sources} ${headers})

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# ---------------------------------------
# atb.networking
# ---------------------------------------
get_platform_independent_static_library_name(atb_networking_library "atb.networking")
set(atb_networking_library ${atb_library_binary_path}/${atb_networking_library})
include_directories(${atb_library_include_path})
message(STATUS "atb -> Networking library:  " ${atb_networking_library})

# ---------------------------------------
# atb.core
# ---------------------------------------
get_platform_independent_static_library_name(atb_core_library "atb.core")
set(atb_core_library ${atb_library_binary_path}/${atb_core_library})
include_directories(${atb_library_include_path})
message(STATUS "atb -> Core library:  " ${atb_core_library})

# --------------------------------------
# atb.common
# --------------------------------------
get_platform_independent_static_library_name(atb_common_library "atb.common")
set(atb_common_library ${atb_library_binary_path}/${atb_common_library})
include_directories(${atb_library_include_path}/${atb_common_target})
message(STATUS "atb -> atb.common library:  " ${atb_common_library})

# ---------------------------------------
# boost
# ---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost include dir:   "      ${Boost_INCLUDE_DIRS})
message(STATUS "atb -> Boost Libraries dir: "    ${Boost_LIBRARIES})

# ---------------------------------------
# set libraries
# ---------------------------------------
target_link_libraries(  ${atb_target} ${atb_networking_library}
                        ${atb_core_library} ${atb_common_library}
                        ${Boost_LIBRARIES})

