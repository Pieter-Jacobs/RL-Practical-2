#include "Maze.hpp"
using namespace std;


void Maze::initializeMaze() 
{ 
    for(int i = 0; i < height_; i++) {
        vector<Field*> row;
        for(int j = 0; j < width_; j++) {
            array<int, 2> coordinates = {i,j};
            row.push_back(new Field(coordinates, width_, height_));
            }
        maze.push_back(row);
    }
}

size_t Maze::getMaxX() const {
    return width_; 
}

size_t Maze::getMaxY() const {
    return height_; 
}

Field* Maze::getField(array<int,2> coordinates) 
{
    return maze[coordinates[0]][coordinates[1]];
}
Maze::Maze(size_t width, size_t height)
    : width_(width), height_(height)
{
    initializeMaze();
}

Maze::~Maze()
{
}
