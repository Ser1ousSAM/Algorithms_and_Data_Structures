cmake_minimum_required(VERSION 3.22.1)
project(cmake_modules)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake_hello
        modules.cpp utils.cpp)
