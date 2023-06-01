cmake_minimum_required(VERSION 3.22.1)
project(task10)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(LZW
        LZW.cpp)
