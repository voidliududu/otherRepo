cmake_minimum_required(VERSION 3.8)
project(Shop)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp Items.cpp Items.h Store.cpp Store.h ShopCart.cpp ShopCart.h Seller.cpp Seller.h)
set(SOURCE_FILES main.cpp Items.cpp Items.h Store.cpp Store.h Seller.cpp Seller.h)
add_executable(Shop ${SOURCE_FILES})