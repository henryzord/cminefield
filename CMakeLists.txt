cmake_minimum_required(VERSION 3.21)
project(cminefield C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_executable(
    cminefield
        src/main.c
        include/ANSI-color-codes.h
        include/definitions.h
)


