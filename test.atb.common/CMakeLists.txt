#-------------------------------------------------------------------------------
# General
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

set(atb_common_test_target "test.atb.common")

set(headers "include/test_message_correction_machine.h")
set(sources "source/test_message_correction_machine.cpp"
            "source/main.cpp")

include_directories("include/")
include_directories(${atb_library_include_path})

message(STATUS "--------------------------------------------------------------")
message(STATUS "-                       test.atb.common                      -")
message(STATUS "--------------------------------------------------------------")

#-------------------------------------------------------------------------------
# Compiler options and target
#-------------------------------------------------------------------------------
project(${atb_common_test_target})
set(CMAKE_SKIP_RPATH ON)
add_executable(${atb_common_test_target} ${sources} ${headers})

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
#---------------------------------------
# atb.common
#---------------------------------------
get_platform_independent_static_library_name(atb_common_library "atb.common")
set(atb_common_library ${atb_library_binary_path}/${atb_common_library})
target_link_libraries(${atb_common_test_target} ${atb_common_library})
message(STATUS "test.atb.common -> atb.common library:  " ${atb_common_library})

#---------------------------------------
# google test
#---------------------------------------
get_platform_independent_static_library_name(google_test_library "gtestd")
set(google_test_library ${atb_library_binary_path}/${google_test_library})
target_link_libraries(${atb_common_test_target} ${google_test_library})
message(STATUS "test.atb.common -> Google test library:  " ${google_test_library})

#---------------------------------------
# boost
#---------------------------------------
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${atb_common_test_target} ${Boost_LIBRARIES})
message(STATUS "test.atb.common -> Boost include dir:    " ${Boost_INCLUDE_DIRS})
message(STATUS "test.atb.common -> Boost Libraries dir:  " ${Boost_LIBRARIES})
