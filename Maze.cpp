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

size_t Maze::getWidth() const {
    return width_; 
}

size_t Maze::getHeight() const {
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

void Maze::print() {
    for(int i = 0; i < height_; i++) {
        for(int q = 0; q < width_; q++) {
            //cout << "{";
            for(int j = 0; j < getField({i,q})->getWalls().size(); j++) {
                //cout << getField({i,q})->getWalls()[j];
                getField({ i,q })->initializeActions();
                //cout << ",";
            }
            //cout << "}";
            //cout << "\n";
        }
    }/*
    cout << "___________\n";
    for (int i = 0; i < height_; i++) {
        cout << '|';
        for (int q = 0; q < width_; q++) {
            int check = 0;
            for (int j = 4; j != 0; j--) {
                if (j == 2 && (getField({ i,q })->getWalls()[j] != 0 || i == height_ - 1)) {
                    cout << "_";
                    check = 1;
                }
                if (j == 1 && getField({ i,q })->getWalls()[j] != 0) {
                    cout << "|";
                    check = 1;
                }
            }
            if (!check) {
                cout << ' ';
            }
        }
        cout << "|";
        cout << "\n";
    }*/
}

void Maze::printActions() {
    for (int i = 0; i < height_; i++) {
        for (int q = 0; q < width_; q++) {
            getField({ i,q })->printActions();
        }
    }
}
