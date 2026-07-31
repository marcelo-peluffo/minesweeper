cmake_minimum_required(VERSION 3.16)
project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Minesweeper src/main.cpp src/Grid.cpp src/Tile.cpp)
target_include_directories(Minesweeper PRIVATE include)
