cmake_minimum_required(VERSION 3.10)
project(Ecrypt)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ecrypt main.cpp Aes.h)
add_executable(rc4 rc4.h rc4test.cpp)

add_executable(skey md5.h md5.cpp skey.cpp)