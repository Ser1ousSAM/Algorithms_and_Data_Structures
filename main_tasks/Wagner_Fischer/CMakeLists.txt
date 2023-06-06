cmake_minimum_required(VERSION 3.22.1)
project(task8)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(L_d
        editorial_distance.cpp Wagner_Fischer.h)
