cmake_minimum_required(VERSION 3.19)
project(CPU6502)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPU6502 main.cpp Memory.cpp Memory.h Types.h)