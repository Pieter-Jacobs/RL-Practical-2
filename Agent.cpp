#include "Agent.hpp"

using namespace std;

Agent::Agent()
{
}

Agent::Agent(Maze* maze, Field* currentField)
    :  maze_(maze), currentField_(currentField)
{
}

Agent::~Agent()
{
}


array<int,2> Agent::getUpdatedCoordinates(int move) {
    array<int, 2> coordinates = currentField_->getCoordinates();
    switch (move)
    {
        // move up
        case 0:
            coordinates[1] -= 1;
            break;
        // move right
        case 1:
            coordinates[0] += 1;
            break;
        // move down
        case 2: 
            coordinates[1] += 1;
            break;
        // move left
        case 3: 
            coordinates[0] -= 1;
            break;
        default:
            break;
    }
    return coordinates;
}

void Agent::DFS() 
{
    vector<Field*> visited;
    visited.push_back(currentField_);
    while (!visited.empty() && !currentField_->isTerminalState())
    {
        cout << currentField_->getCoordinates()[0] << " " << currentField_->getCoordinates()[1] << "\n";
        visited.pop_back();
        array<int,2> coordinates = currentField_->getCoordinates();
        vector<int> possibleMoves;
        for(int i = 0; i < 4; i++) {
            // if the new field is not visited yet and the move does not get the agent
            // outside of the grid, the move is possible
            if(currentField_->getAvailableMoves()[i] != -1 &&
            (find(visited.begin(), visited.end(), maze_->getField(getUpdatedCoordinates(i))) 
            == visited.end())) {
                possibleMoves.push_back(i);
            }
        }
        int move_ = possibleMoves[rand()%possibleMoves.size()];
        // cout << move_;
        move(move_);
        visited.push_back(currentField_);
    }
    
}

void Agent::move(int move)
{
    array<int, 2> coordinates = getUpdatedCoordinates(move);
    currentField_ = maze_->getField(coordinates);
}

