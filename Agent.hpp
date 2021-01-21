#include "Maze.hpp"
#include "Field.hpp"
#include<stack>
#include<vector>
#include<array>
#include<iostream>

#pragma once 

class Agent
{
    private:
        double score;
    protected: 
        Maze* maze_;
        Field* currentField_;
    public:
        Agent();
        Agent(Maze* maze, Field* currentField);
        Maze* getMaze() const;
        std::array<int,2> getUpdatedCoordinates(int move);
        std::array<int,2> getUpdatedCoordinates(std::array<int,2> coordinates, int move);
        void move(int move);
};
