#include "Maze.hpp"
#include "Field.hpp"
#include<vector>
#include<iostream>

#pragma once 

class Agent
{
    private:
        Field* currentField_;
        Maze* maze_;
    public:
        Agent();
        Agent(Maze* maze, Field* currentField);
        ~Agent();
        void DFS();
        void move(std::array<int,2> coordinates, int move);
};
