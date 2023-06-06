cmake_minimum_required(VERSION 3.22.01)
project(task_a)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_a
        RefStrings.cpp _str.h Str.h)
