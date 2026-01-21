cmake_minimum_required(VERSION 4.0)
project(wisielec_programowanie_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(wisielec_programowanie_1 main.cpp
        models.h
        game_logic.h
        display.h
        game_logic.cpp
        display.cpp
        settings.cpp
        settings.h
        categories_logic.cpp
        categories_logic.h
        fileOperations.cpp
        fileOperations.h)
