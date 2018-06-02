cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 11)

add_executable(code main.cpp )
add_executable(close closepoint.cpp )
add_executable(kth kth.cpp)
add_executable(8puzzle 8puzzle.c)
add_executable(knapspack knapspack.cpp)
add_executable(kmp kmp.cpp)

add_executable(flyed Flyed.cpp)

add_executable(prime prime.cpp)
