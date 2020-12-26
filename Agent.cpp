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

void Agent::DFS() 
{
    // vector<Field*> visited;
    // visited.push_back(currentField);
    // while (!visited.empty() && !currentField->isTerminalState())
    // {
    //     currentField = visited.pop_back();
    //     array<int,2> coordinates = currentField->getCoordinates();
    //     for(int move : currentField->getAvailableMoves()) {
        
    //     }
    // }
    
}

void Agent::move(array<int,2> coordinates, int move)
{
    switch (move)
    {
    // move left
    case 0:
        
        break;
    // move up
    case 1:
        break;
    // move right
    case 2: 
        break;
    // move down
    case 3: 
        break;
    default:
        break;
    }
}

