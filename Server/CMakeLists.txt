cmake_minimum_required(VERSION 3.24)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp tcpServer.cpp tcpServer.h inputDataHandling.h inputDataHandling.cpp)
