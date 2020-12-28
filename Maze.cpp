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


// void Maze::print() {
//     for(int i = 0; i < height_; i++) {
//         for(int q = 0; q < 3; q++) {
//             for(int j = 0; j < width_; j++) {
//                 array<int,4> moves = maze[i][j]->getAvailableMoves();
//                 if(q==0 && (moves[0] == -1 || moves[0] == 0)) {
//                     cout << "---";
//                 } else if(q==0 && moves[0] == 1) {
//                     cout << "   ";
//                 }
//                 if(q==1 && (moves[3] == -1 || moves[3] == 0)) {
//                     cout << "|";
//                 } else if(q==1 && moves[3] == 1) {
//                     cout << " ";
//                 }
//                 if(q==1){
//                     cout << " ";
//                 }
//                 if(q==1 && (moves[1] == -1 || moves[1] == 0)) {
//                     cout << "|";
//                 } else if(q==1 && moves[1] == 1) {
//                     cout << " ";
//                 }

//                 if(q==2 && (moves[2] == -1 || moves[2] == 0)) {
//                     cout << "---";
//                 } else if(q==0 && moves[0] == 1) {
//                     cout << "   ";
//                 }
//                 if(j == width_-1) {
//                     cout << "\n";
//                 }
//             }
//         }
//     }
// }
