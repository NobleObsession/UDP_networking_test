cmake_minimum_required(VERSION 3.17)
include(FetchContent)

project(UDP_networking_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(${Boost_INCLUDE_DIR})

add_executable(UDP_networking_test main.cpp UDP_server.cc thread_util.cc)

target_link_libraries(UDP_networking_test ${Boost_LIBRARIES})

