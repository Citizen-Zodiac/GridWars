cmake_minimum_required(VERSION 3.20)
project(GridWars)

set(CMAKE_CXX_STANDARD 14)

add_executable(GridWars Main.cpp
        GAMES/numerical_tic.cpp "GAMES/Misere.h" "GAMES/Misere_Board.cpp" "GAMES/obstacles_xo.h" "GAMES/sus.h" "GAMES/xo_5.h" "GAMES/obstacles_xo.cpp" "GAMES/sus.cpp" "GAMES/xo_5.cpp" "GAMES/tic_4x4.cpp")
