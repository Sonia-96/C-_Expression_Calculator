cmake_minimum_required(VERSION 3.24)
project(MSDScript)

set(CMAKE_CXX_STANDARD 17)

add_executable(MSDScript main.cpp cmdline.cpp cmdline.h expr.cpp expr.h tests.cpp parser.cpp parser.h fuzzing.cpp fuzzing.h exec.cpp exec.h)
