cmake_minimum_required(VERSION 3.11.0)

#--------------------------------------------------------------------------------------------------
# General
#--------------------------------------------------------------------------------------------------
set(atb_target atb)

project(${atb_target} VERSION 0.0.1 LANGUAGES CXX)

#--------------------------------------------------------------------------------------------------
# Compiler config
#--------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SKIP_RPATH ON)

#--------------------------------------------------------------------------------------------------
# Project
#--------------------------------------------------------------------------------------------------
set(sources "main.cpp")
set(headers "")

add_executable(${atb_target} ${sources} ${headers})

#--------------------------------------------------------------------------------------------------
# Project dependencies
#--------------------------------------------------------------------------------------------------
set(spdlog_include_directory "spdlog/include/")
target_include_directories(${atb_target} PUBLIC ${spdlog_include_directory})

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost 1.66.0 EXACT REQUIRED thread system)
if(Boost_FOUND)
    message(STATUS "Boost Include directory: "  ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost Library directory: "  ${Boost_LIBRARY_DIRS})
    message(STATUS "Boost Libraries: "          ${Boost_LIBRARIES})

    target_include_directories(${atb_target} PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(${atb_target} ${Boost_LIBRARIES})

endif(Boost_FOUND)
