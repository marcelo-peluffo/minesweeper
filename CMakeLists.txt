cmake_minimum_required(VERSION 3.16)
project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(
    Minesweeper
    src/main.cpp
    src/Tile.cpp
    src/GameContext.cpp
    src/MSWindow.cpp
    src/Grid.cpp
    src/Game.cpp
)

target_include_directories(Minesweeper PRIVATE include)
target_link_libraries(
    Minesweeper PRIVATE
    SFML::Graphics 
    SFML::Window 
    SFML::System
)
