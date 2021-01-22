# cmake_minimum_required(VERSION <specify CMake version here>)
project(RL_Practical_2_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RL_Practical_2_main
        Agent.cpp
        Agent.hpp
        AgentDFS.cpp
        AgentDFS.hpp
        Field.cpp
        Field.hpp
        main.cpp
        main.hpp
        Maze.cpp
        Maze.hpp)
