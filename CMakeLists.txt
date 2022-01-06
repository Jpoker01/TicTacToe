cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToe main.cpp Engine.cpp Engine.h Layout.cpp Layout.h Position.cpp Position.h Size.cpp Size.h Player.cpp Player.h)