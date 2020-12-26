#include<iostream>
#include<array>
#include<vector>
#include<stdlib.h>
#include "Field.hpp"
#include "Agent.hpp"

#pragma once

class Maze
{           
    private:
        std::vector<std::vector<Field*>> maze;
        Agent agent;
        size_t width_;
        size_t height_;
        void initializeMaze();

    public:
        Maze(size_t width, size_t height);
        ~Maze();
        Field* getField(std::array<int,2> coordinates);
};