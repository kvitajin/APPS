cmake_minimum_required(VERSION 3.8)
project(APPS2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp font8x8.cpp font36.cpp template.cpp)
add_executable(APPS2 ${SOURCE_FILES})