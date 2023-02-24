cmake_minimum_required(VERSION 3.24)
project(MSDScript)

set(CMAKE_CXX_STANDARD 17)

add_executable(MSDScript main.cpp cmdline.cpp cmdline.h expr.cpp expr.h tests.cpp parser.cpp parser.h)
add_executable(TestMSDScript fuzz_test.cpp expr.cpp expr.h exec.cpp exec.h expr_gen.cpp expr_gen.h)
add_executable(TestExprGenerator test_expr_gen.cpp expr_gen.cpp expr_gen.h expr_gen_test.cpp expr.cpp expr.h)