cmake_minimum_required(VERSION 3.8)
project(DownLiud)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Controller.cpp include/Controller.h model/FileManager.cpp include/FileManager.h model/Downloader/Downloader.cpp include/Downloader.h lib/Url.cpp include/Url.h lib/net/Http.cpp include/Http.h include/exception.h lib/net/Tcp.cpp include/Tcp.h Config.cpp include/Config.h Connect.cpp include/Connect.h)
#set(SOURCE_FILES main.cpp)
add_executable(DownLiud ${SOURCE_FILES})