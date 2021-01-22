#include "Agent.hpp"

using namespace std;

Agent::Agent()
{
}

Agent::Agent(Maze* maze, Field* currentField)
    :  maze_(maze), currentField_(currentField)
{
}
array<int,2> Agent::getUpdatedCoordinates(int move) {
    array<int, 2> coordinates = currentField_->getCoordinates();
    coordinates = getUpdatedCoordinates(coordinates, move);
    return coordinates;
}

array<int,2> Agent::getUpdatedCoordinates(array<int,2> coordinates, int move) {
    switch (move)
    {
        // move up
        case 0:
            coordinates[0] -= 1;
            break;
        // move right
        case 1:
            coordinates[1] += 1;
            break;
        // move down
        case 2: 
            coordinates[0] += 1;
            break;
        // move left
        case 3: 
            coordinates[1] -= 1;
            break;
        default:
            break;
    }
    return coordinates;
}

Maze* Agent::getMaze() const {
    return maze_;
}

double Agent::getReward(Field* state) {
    if(state->isTerminalState()) {
        return 100;
    }
    return -1;
}

void Agent::move(int move)
{
    array<int, 2> coordinates = getUpdatedCoordinates(move);   
    // cout << "moved to: " << coordinates[0] << " " << coordinates[1] << "\n";
    currentField_ = maze_->getField(coordinates);
}