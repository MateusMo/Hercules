cmake_minimum_required(VERSION 4.2)
project(Hercules C)

set(CMAKE_C_STANDARD 11)

add_executable(Hercules main.c
        animation.c
        animation.h
        messages.c
        messages.h)
