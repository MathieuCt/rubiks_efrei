cmake_minimum_required(VERSION 3.19)
project(rubiks_efrei C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(rubiks_efrei
        tests_ncurses.c main.c)
