#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
set(CMAKE_MIN_VERSION 3.9.0)
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

cmake_policy(SET CMP0060 NEW)
enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/defines/platform_definitions.txt)

get_binary_path(atb_library_binary_path)
get_include_path(atb_library_include_path)

set(BOOST_VERSION 1.62.0)
include_directories(${atb_library_include_path})

#-------------------------------------------------------------------------------
# Project and Project dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# spdlog
#---------------------------------------
set(spd_log_include "spdlog/include/")
include_directories(${spd_log_include})

#---------------------------------------
# boost
#---------------------------------------
set(Boost_USE_STATIC_LIBS ON)                           # only find static libs
find_package(Boost ${BOOST_VERSION} EXACT REQUIRED thread system regex)
if(Boost_FOUND)
    message(STATUS "Boost Include directory: "  ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost Library directory: "  ${Boost_LIBRARY_DIRS})
    message(STATUS "Boost Libraries: "          ${Boost_LIBRARIES})
endif(Boost_FOUND)

#---------------------------------------
# atb.common and test.atb.common
#---------------------------------------
set(atb_common_target "atb.common")
set(atb_common_test_target "test.atb.common")

add_subdirectory(${atb_common_target})
add_subdirectory(${atb_common_test_target})

add_test(NAME ${atb_common_test_target} COMMAND ${atb_common_test_target})

#---------------------------------------
# atb.networking
#---------------------------------------
set(atb_networking_target "atb.networking")
add_subdirectory(${atb_networking_target})

#---------------------------------------
# atb.core
#---------------------------------------
set(atb_core_target "atb.core")
add_subdirectory(${atb_core_target})

#---------------------------------------
# atb
#---------------------------------------
set(atb_target "atb")
add_subdirectory(${atb_target})

#-------------------------------------------------------------------------------
# Build order main program and tests
#-------------------------------------------------------------------------------
#---------------------------------------
# Build order main program
#---------------------------------------
add_dependencies(${atb_core_target} ${atb_common_target})
add_dependencies(${atb_networking_target} ${atb_common_target})

add_dependencies(${atb_target} ${atb_networking_target} ${atb_core_target})

#---------------------------------------
# Build order test
#---------------------------------------
add_dependencies(${atb_common_test_target} ${atb_common_target})

#-------------------------------------------------------------------------------
# Output for all targets
#-------------------------------------------------------------------------------
set_target_properties(
    # libraries and main program
    ${atb_common_target} ${atb_core_target}
    ${atb_networking_target} ${atb_target}

    # test programs
    ${atb_common_test_target}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${atb_library_binary_path}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${atb_library_binary_path}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${atb_library_binary_path}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${atb_library_binary_path}
)

set_target_properties(
    # libraries and main program
    ${atb_common_target} ${atb_core_target}
    ${atb_networking_target} ${atb_target}

    # test programs
    ${atb_common_test_target}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${atb_library_binary_path}
    RUNTIME_OUTPUT_DIRECTORY ${atb_library_binary_path}
    ARCHIVE_OUTPUT_DIRECTORY ${atb_library_binary_path}
    RUNTIME_OUTPUT_DIRECTORY ${atb_library_binary_path}
)