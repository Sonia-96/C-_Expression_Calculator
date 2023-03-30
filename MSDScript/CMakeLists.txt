cmake_minimum_required(VERSION 3.24)
project(MSDScript)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(MSDScript main.cpp cmdline.cpp cmdline.h expr.cpp expr.h tests.cpp parser.cpp parser.h val.cpp val.h pointer.h)
add_executable(TestMSDScript fuzzTest.cpp expr.cpp expr.h exec.cpp exec.h ExprGen.cpp ExprGen.h val.cpp val.h pointer.h)
add_executable(TestExprGenerator ExprGen.cpp ExprGen.h ExprGenTest.cpp expr.cpp expr.h val.cpp val.h pointer.h)