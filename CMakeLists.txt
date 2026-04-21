cmake_minimum_required(VERSION 3.20)
project(Hercules C)

set(CMAKE_C_STANDARD 11)

add_executable(Hercules
        src/main.c
        src/animation.c
        src/messages.c
        src/commands/clear.c
        src/commands/find.c
)

target_include_directories(Hercules PRIVATE include)