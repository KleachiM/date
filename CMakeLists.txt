cmake_minimum_required(VERSION 3.24)
project(date)

set(CMAKE_CXX_STANDARD 20)

add_executable(date main.cpp Date.cpp Date.h)
add_subdirectory(tests)
