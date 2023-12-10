cmake_minimum_required(VERSION 3.26)
project(TetrisLab)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6.1 COMPONENTS graphics REQUIRED)

add_executable(TetrisLab main.cpp
        settings.cpp
        TetrisGame.cpp
)

target_link_libraries(TetrisLab sfml-graphics)
