cmake_minimum_required(VERSION 3.25)
project(ProjetoFinal C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(ProjetoFinal
        src/main.c
)
