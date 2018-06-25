cmake_minimum_required(VERSION 3.6)
project(project4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp function.cpp function.h variable.cpp variable.h graph.cpp graph.h)
add_executable(project4 ${SOURCE_FILES})