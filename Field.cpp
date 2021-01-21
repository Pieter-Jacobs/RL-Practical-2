#include "Field.hpp"

using namespace std;

double Field::getReward() const
{
    //cout << "Coordinates = " << coordinates_[0] << ", " << coordinates_[1] << '\n';
    return reward;
};

bool Field::isTerminalState() const
{
    return terminalState;
}

array<int, 4> Field::getWalls() const
{
    return walls;
}

array<int, 2> Field::getCoordinates() const
{
    return coordinates_;
}

array<double, 4> Field::getActions()
{
    return actions_;
}

void Field::printActions()                              //print all Q-values of this state
{
    cout << '[';
    for (size_t i = 0; i < 4; ++i) {
        cout << actions_[i] << ", ";
    }
    cout << "]\n";
}

void Field::updateAction(int action, double value)      //Change the Q-value of the state-action pair
{
    actions_[action] = value;
}

void Field::removeWall( int move )
{
    walls[move] = 0; 
}

Field::Field(array<int, 2> coordinates, size_t mazeWidth, size_t mazeHeight)
    : coordinates_(coordinates), walls{ 1,1,1,1 }, actions_{0,0,0,0}
{
    // Create edges of the maze
    if(coordinates[0] - 1 < 0) {
        walls[0] = -1;
    }
    if(coordinates[1] + 1 > (mazeWidth-1)) {
        walls[1] = -1;
    }
    if(coordinates[0] + 1 > (mazeHeight-1)) {
        walls[2] = -1;
    }
    if(coordinates[1] - 1 < 0) {
        walls[3] = -1;
    }
    
    // If the cell is in the bottom right of the maze, it is the terminal state.
    if(coordinates[0] == (mazeWidth-1) && coordinates[1] == (mazeHeight-1)) {
        terminalState = true;
        reward = 0;                                 //The reward of the terminal state is 0
    }
}

Field::~Field()
{
}
