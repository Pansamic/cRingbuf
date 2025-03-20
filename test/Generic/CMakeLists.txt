# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Specify the name of the project and the language
project(cringbuf_test C)

# Add the directory where cringbuf.h is located
include_directories(../../)

# Add the executable for the test program and the cringbuf source file
add_executable(cringbuf_test ../cringbuf_test.c ../../cringbuf.c)
