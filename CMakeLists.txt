cmake_minimum_required(VERSION 3.19)
project(rubiks_efrei C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(rubiks_efrei main.c draw.c draw.h rubiks.c rubiks.h moves_rubiks.c moves_rubiks.h)

target_link_libraries(rubiks_efrei curses)
