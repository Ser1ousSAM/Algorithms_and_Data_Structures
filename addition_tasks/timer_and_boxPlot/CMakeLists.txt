cmake_minimum_required(VERSION 3.22.1)
project(timer_and_boxPlot)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(timer_and_boxPlot
        BoxPlot.h
        Main.cpp
        Timer.h)
