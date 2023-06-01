cmake_minimum_required(VERSION 3.22.1)
project(prefix_tree)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(prefix_tree
        Main.cpp
        PrefixTree.cpp
        PrefixTree.h)
