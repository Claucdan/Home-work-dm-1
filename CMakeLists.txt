cmake_minimum_required(VERSION 3.27)
project(dm)

set(CMAKE_CXX_STANDARD 17)

add_executable(dm main.cpp
        graph.cpp
        graph.h)
