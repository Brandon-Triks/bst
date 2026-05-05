cmake_minimum_required(VERSION 4.0)
project(bst)

set(CMAKE_CXX_STANDARD 20)

add_executable(bst main.cpp
        source.cpp
        header.h)
