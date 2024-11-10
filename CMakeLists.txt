cmake_minimum_required(VERSION 3.29)
project(HuffmanFileZipper)

set(CMAKE_CXX_STANDARD 20)

add_executable(HuffmanFileZipper main.cpp
        PriorityQueue.cpp
        Node.cpp
        Node.h)
