cmake_minimum_required(VERSION 3.23)
project(GameOfLife C)

set(CMAKE_C_STANDARD 99)

add_executable(GameOfLife main.c
                BMPs.c
                BMPs.h
                GoL.c
                GoL.h)