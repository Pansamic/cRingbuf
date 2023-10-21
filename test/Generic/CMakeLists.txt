# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Specify the name of the project and the language
project(cRingbuf_test C)

# Add the directory where cRingbuf.h is located
include_directories(../../)

# Add the executable for the test program and the cRingbuf source file
add_executable(cRingbuf_test cRingbuf_test.c ../../cRingbuf.c)
