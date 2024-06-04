cmake_minimum_required(VERSION 3.28)
project(JUDGE)

set(CMAKE_CXX_STANDARD 17)

add_executable(JUDGE main.cpp
        robot.h
        robot.cpp
        main.h
)
