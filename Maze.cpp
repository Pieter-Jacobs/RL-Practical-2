#include<vector>
#include "Maze.hpp"

using namespace std;


void Maze::initializeMaze() 
{ 
    for(int i = 0; i < height_; i++) {
        vector<Field*> row;
        for(int j = 0; j < width_; j++) {
            row.push_back(new Field());
            row[j]->getReward();
        }
        grid.push_back(row);
    }
}

Maze::Maze(size_t width, size_t height)
    : width_(width), height_(height)
{
    initializeMaze();
}

Maze::~Maze()
{
}
