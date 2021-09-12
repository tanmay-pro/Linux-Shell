cmake_minimum_required(VERSION 3.17)
project(goyshell C)

set(CMAKE_C_STANDARD 11)

add_executable(goyshell main.c include/function_def.h source/prompt.c source/string_func.c source/echo.c source/commander.c)