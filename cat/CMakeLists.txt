cmake_minimum_required(VERSION 3.3)
project(cat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES cat.c)
add_executable(cat ${SOURCE_FILES})