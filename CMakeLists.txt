cmake_minimum_required(VERSION 3.20)
project(GridWars)

set(CMAKE_CXX_STANDARD 14)

add_executable(GridWars Main.cpp
        GAMES/XO_Classes.cpp)