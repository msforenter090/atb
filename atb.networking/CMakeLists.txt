#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_networking_target "atb.networking")

set(headers "include/def.h"
            "include/network_client.h"
            "include/network_junction.h")
set(sources "source/network_client.cpp"
            "source/network_junction.cpp")

include_directories("include/")
add_library(${atb_networking_target} STATIC ${sources} ${headers})
set_property(TARGET ${atb_networking_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# boost
#---------------------------------------
set(Boost_USE_STATIC_LIBS ON)                           # only find static libs
find_package(Boost 1.62.0 EXACT REQUIRED thread system regex)
if(Boost_FOUND)
    message(STATUS "Boost Include directory: "  ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost Library directory: "  ${Boost_LIBRARY_DIRS})
    message(STATUS "Boost Libraries: "          ${Boost_LIBRARIES})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${atb_networking_target} ${Boost_LIBRARIES})
endif(Boost_FOUND)
