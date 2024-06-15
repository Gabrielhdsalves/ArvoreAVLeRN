cmake_minimum_required(VERSION 3.28)
project(rubronegra C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(arvores)

add_executable(rubronegra
        arvores/avl.c
        arvores/avl.h
        arvores/rubroNegra.c
        arvores/rubroNegra.h
        funcoesBasicas.c
        funcoesBasicas.h
        main.c)
