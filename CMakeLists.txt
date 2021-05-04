cmake_minimum_required(VERSION 3.19)
project(rubiks_efrei C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(rubiks_efrei main.c draw.c draw.h structur_rubiks.c structur_rubiks.h)

target_link_libraries(rubiks_efrei curses)
