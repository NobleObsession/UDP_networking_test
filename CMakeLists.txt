cmake_minimum_required(VERSION 3.17)
project(UDP_networking_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "g++-10")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(UDP_networking_test main.cpp UDP_server.cc thread_util.cc)

target_link_libraries(UDP_networking_test ${CONAN_LIBS})

file(COPY ${CMAKE_SOURCE_DIR}/test_client.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/test_output.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

