#include "AgentQLearning.hpp";

using namespace std; 

AgentQLearning::AgentQLearning() {
    for(int i=0; i < maze_->getHeight(); i++) {
        vector<vector<double>> row(maze_->getWidth(),{{0,0,0,0}}); 
        qTable.push_back(row);
    }
}

void AgentQLearning::solveMaze() {
    std::mt19937 gen(1729);
    uniform_real_distribution<double> dist(0,1);

    if (dist(gen) <= epsilon) {
        // explore
        cout << "EXPLORATION" << "\n";
        updateQTable(getRandomMove());
    }
    else {
        // exploit
        cout << "EXPLOIT" << "\n";
    }
}

vector<int> determinePossibleMoves() { 

}

void AgentQLearning::selectAction() {

}

void AgentQLearning::updateQTable(int move) {
    array<int,2> coordinates = currentField_->getCoordinates();
    if(currentField_->getWalls()[move] == 0) {
        // update state action value with bellman equation
        qTable[coordinates[0]][coordinates[1]][move] += alpha*(-1) + gamma * 
        (calculateQValue(move, maze_->getField(getUpdatedCoordinates(move))));
        // Agent hit a wall so starts anew
        currentField_ = maze_->getField({0,0});
    };

}

double AgentQLearning::calculateQValue(int move, Field* newState) {
    array<int,2> coordinates = 
    for(int i = 0; i < 4; i++) {    
        qTable[coordinates[0]][coordinates[1]][i] += alpha*(-1) + gamma * ();
    }
}

int getRandomMove() {
    return rand()%4;
}
