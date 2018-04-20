#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
set(CMAKE_MIN_VERSION 3.9.0)
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(atb_target atb)

project(${atb_target} VERSION 0.0.1 LANGUAGES CXX)

#-------------------------------------------------------------------------------
# Compiler config
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SKIP_RPATH ON)

#-------------------------------------------------------------------------------
# Project
#-------------------------------------------------------------------------------
set(headers "thread_safe_queue.h"
            "ip_address_v4.h"
            "network_message.h"
            "network_client.h"
            "network_junction.h")

set(sources "main.cpp"
            "thread_safe_queue.cpp"
            "network_client.cpp"
            "network_junction.cpp")

add_executable(${atb_target} ${sources} ${headers})

#-------------------------------------------------------------------------------
# Project dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# spdlog
#---------------------------------------
set(spdlog_include_directory "spdlog/include/")
target_include_directories(${atb_target} PUBLIC ${spdlog_include_directory})

#---------------------------------------
# boost
#---------------------------------------
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost 1.62.0 EXACT REQUIRED thread system regex)
if(Boost_FOUND)
    message(STATUS "Boost Include directory: "  ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost Library directory: "  ${Boost_LIBRARY_DIRS})
    message(STATUS "Boost Libraries: "          ${Boost_LIBRARIES})

    target_include_directories(${atb_target} PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(${atb_target} ${Boost_LIBRARIES})

endif(Boost_FOUND)

#---------------------------------------
# atb.networking
#---------------------------------------

#---------------------------------------
# atb.core
#---------------------------------------