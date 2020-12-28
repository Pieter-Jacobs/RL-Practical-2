#include "Field.hpp"

using namespace std; 

double Field::getReward() const 
{
    cout << "Reward = " << reward << "\n";
    return reward;
};

bool Field::isTerminalState() const
{
    return terminalState;
}

array<int, 4> Field::getAvailableMoves() const
{
    return availableMoves;
}

array<int, 2> Field::getCoordinates() const
{   
    return coordinates_;
}

void Field::removeWall(int wall)
{
    availableMoves[wall] = 1;
}

Field::Field(array<int, 2> coordinates, size_t mazeWidth, size_t mazeHeight)
    : coordinates_(coordinates), availableMoves({0,0,0,0})
{
    // Create edges of the maze
    if(coordinates[1] - 1 < 0) {
        availableMoves[0] = -1;
    }
    if(coordinates[0] + 1 > (mazeWidth-1)) {
        availableMoves[1] = -1;
    }
    if(coordinates[1] + 1 > (mazeHeight-1)) {
        availableMoves[2] = -1;
    }
    if(coordinates[0] - 1 < 0) {
        availableMoves[3] = -1;
    }

    // If the cell is in the bottom right of the maze, it is the terminal state.
    if(coordinates[0] == (mazeWidth-1) && coordinates[1] == (mazeHeight-1)) {
        terminalState = true;
    }
    // uniform_int_distribution<double> urd(-1.0, 1.0);
    // cout << rand() << "\n";
    // default_random_engine e(rand());
    // reward = urd(e);
}

Field::~Field()
{
}
