#include "AgentTemporal.hpp"

using namespace std;

AgentTemporal::AgentTemporal(/* args */)
{
}

int AgentTemporal::getRandomMove(vector<int> availableMoves) {
    return availableMoves[rand()%availableMoves.size()];
}

vector<int> AgentTemporal::getAvailableMoves(Field* state) { 
    vector<int> availableMoves; 
    array<int,4> obstacles = state->getWalls();
    for(int i = 0; i<4; i++) {
        if(obstacles[i] == 0) {
            availableMoves.push_back(i);
        }
    }
    return availableMoves;
}

int AgentTemporal::chooseActionEpsilonGreedy() {
    if(d(g) <= epsilon) {
        return getRandomMove(getAvailableMoves(currentField_));
    }
    return getQLearningMove(getAvailableMoves(currentField_));
}

int AgentTemporal::getQLearningMove(vector<int> availableMoves) {
    array<int,2> coordinates = currentField_->getCoordinates();
    double bestQ = qTable[coordinates[0]][coordinates[1]][availableMoves[0]];
    int bestMove = availableMoves[0];
    for(int i = 1; i < availableMoves.size(); i++) {
        // cout << "Q possible:" << qTable[coordinates[0]][coordinates[1]][availableMoves[i]] << "\n";
        if(qTable[coordinates[0]][coordinates[1]][availableMoves[i]] > bestQ) {
            bestQ = qTable[coordinates[0]][coordinates[1]][availableMoves[i]];
            bestMove = availableMoves[i];
        } 
    }
    // cout << "Q chosen: " << bestQ << "\n";
    return bestMove;
}