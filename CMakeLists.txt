cmake_minimum_required(VERSION 3.17)
include(FetchContent)

project(UDP_networking_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

find_package(Boost REQUIRED COMPONENTS system thread)
FIND_PACKAGE(Boost 1.71.0 REQUIRED COMPONENTS system thread regex)

include_directories(${Boost_INCLUDE_DIR})

add_executable(UDP_networking_test main.cpp UDP_server.cc UDP_client.cc)

target_link_libraries(UDP_networking_test ${Boost_LIBRARIES})

enable_testing()

add_executable(
  unit_test
  UDP_server_unit_test.cc
  UDP_client.cc
  UDP_server.cc
)
target_link_libraries(
  unit_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)

