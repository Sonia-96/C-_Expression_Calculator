cmake_minimum_required(VERSION 3.24)
project(hw2_expression)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw2_expression
        main.cpp
        cmdline.cpp
        cmdline.h
        expr.cpp
        expr.hpp
        tests.cpp)
