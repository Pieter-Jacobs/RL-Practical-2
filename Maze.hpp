#pragma once

#include<iostream>
#include<array>
#include<vector>
#include<stdlib.h>
#include "Field.hpp"

class Maze
{           
    private:
        std::vector<std::vector<Field*>> maze;
        size_t width_;
        size_t height_;
        void initializeMaze();

    public:
        Maze(size_t width, size_t height);
        ~Maze();
        Field* getField(std::array<int,2> coordinates);
        size_t getWidth() const;
        size_t getHeight() const;
        void print();
        void printActions();
};