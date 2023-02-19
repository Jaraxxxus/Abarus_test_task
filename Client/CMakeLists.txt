cmake_minimum_required(VERSION 3.24)
project(Client)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp SharedBuffer.cpp SharedBuffer.h tcpClient.cpp tcpClient.h handlingFunc.cpp handlingFunc.h)
