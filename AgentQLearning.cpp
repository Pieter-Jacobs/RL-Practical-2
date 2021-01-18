#include "AgentQLearning.hpp";

using namespace std; 

AgentQLearning::AgentQLearning() {
    Maze* maze = this->getMaze();
    for(int i=0; i < maze->getHeight(); i++) {
        vector<vector<double>> row(maze->getWidth(),{{0,0,0,0}}); 
        qTable.push_back(row);
    }
}

vector<int> determinePossibleMoves() { 

}
void AgentQLearning::selectAction() {

}

void AgentQLearning::updateQTable() {
    
}

double AgentQLearning::calculateQValue(int move, Field* state) {
    Field* newState = this->getMaze()->getField(this->getUpdatedCoordinates(move))
}