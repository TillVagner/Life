cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")
add_executable(GameOfLife ${SOURCES})

