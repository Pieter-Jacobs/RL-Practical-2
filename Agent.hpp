#include "Maze.hpp"
#include "Field.hpp"
#include<stack>
#include<vector>
#include<array>
#include<iostream>

#pragma once 

class Agent
{
    protected: 
        Maze* maze_;
        Field* currentField_;
        std::array<int,2> getUpdatedCoordinates(int move);
        std::array<int,2> getUpdatedCoordinates(std::array<int,2> coordinates, int move);
        Maze* getMaze() const;
        void move(int move);
    public:
        Agent();
        Agent(Maze* maze, Field* currentField);
};
