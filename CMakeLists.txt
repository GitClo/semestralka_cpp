cmake_minimum_required(VERSION 3.30)
project(semestralka_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(semestralka_cpp main.cpp
        list.h
        citizen.h
        plot.h)
