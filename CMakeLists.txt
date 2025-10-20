cmake_minimum_required(VERSION 3.27)
project(Trabalho)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(Trabalho
        jardim.cpp
        main.cpp
        Comandos.cpp
)
