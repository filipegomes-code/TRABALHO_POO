cmake_minimum_required(VERSION 3.27)
project(Trabalho)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Trabalho
        jardim.cpp
        jardim.h
        main.cpp
        Settings.h)
