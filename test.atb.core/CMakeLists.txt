#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_core_test_target "test.atb.core")

set(headers "include/test_zone_cashier.h")
set(sources "source/test_zone_cashier.cpp"
            "source/main.cpp")

include_directories("include/")
include_directories(${atb_library_include_path})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                        test.atb.core                       -")
message(STATUS "--------------------------------------------------------------")

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
project(${atb_core_test_target})
set(CMAKE_SKIP_RPATH ON)
add_executable(${atb_core_test_target} ${sources} ${headers})

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# atb.core
#---------------------------------------
get_platform_independent_static_library_name(atb_core_library "atb.core")
set(atb_core_library ${atb_library_binary_path}/${atb_core_library})
target_link_libraries(${atb_core_test_target} ${atb_core_library})
message(STATUS "test.atb.core -> atb.core library:  " ${atb_core_library})

#---------------------------------------
# google test
#---------------------------------------
get_platform_independent_static_library_name(google_test_library "gtestd")
set(google_test_library ${atb_library_binary_path}/${google_test_library})
target_link_libraries(${atb_core_test_target} ${google_test_library})
message(STATUS "test.atb.core -> Google test library:  " ${google_test_library})

#---------------------------------------
# boost
#---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${atb_core_test_target} ${Boost_LIBRARIES})
message(STATUS "test.atb.core -> Boost include dir:    " ${Boost_INCLUDE_DIRS})
message(STATUS "test.atb.core -> Boost Libraries dir:  " ${Boost_LIBRARIES})
