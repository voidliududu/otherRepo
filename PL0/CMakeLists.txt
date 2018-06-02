cmake_minimum_required(VERSION 3.10)
project(PL0 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(PL0 main.c PL0.h)
add_executable(clex clex.c)

project(T CXX)

add_executable(plang LL1.h LL1.c)