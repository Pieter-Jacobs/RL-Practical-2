#include<vector>
#include<stdlib.h>
#include "Field.hpp"

#pragma once

class Maze
{           
    private:
        std::vector<std::vector<Field*>> grid;
        size_t width_;
        size_t height_;
        void initializeMaze();
    public:
        Maze(size_t width, size_t height);
        ~Maze();
};