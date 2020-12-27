#include "Maze.hpp"
#include "Field.hpp"
#include<stack>
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
        std::array<int,2> getUpdatedCoordinates(int move);
        void chooseMoveRandom(std::vector<int> possibleMoves);
        void move(int move);
};
