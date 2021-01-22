#include "AgentQLearning.hpp"

using namespace std; 

AgentQLearning::AgentQLearning() {
}

AgentQLearning::AgentQLearning(Maze* maze, Field* currentField)
{
    maze_ = maze;
    currentField_ = currentField;

    mt19937 gen(1729);
    uniform_real_distribution<double> dist(0,1);
    g = gen;
    d = dist;
    for(int i=0; i < maze_->getHeight(); i++) {
        vector<vector<double>> row(maze_->getWidth(),{{0,0,0,0}}); 
        qTable.push_back(row);
    }
}

void AgentQLearning::solveMaze() {
    int steps = 0;
    for(int i = 0; i < episodes; i++) {
        cout << steps << "\n";
        steps = 0;
        cout << i << "\n";
        // set agent back to starting field
        currentField_ = maze_->getField({0,0});

        // cout << "EPSILON:" << epsilon << "\n";
        while(!currentField_->isTerminalState()) {
            vector<int> availableMoves = getAvailableMoves(currentField_);
            array<int,2> coordinates = currentField_->getCoordinates();
            int move_; 
            move_ = chooseActionEpsilonGreedy();
            //update the state action pair according to reward
            updateQTable(coordinates, move_);
            move(move_);
            steps++;
        }
        printQTable();
        epsilon *= 0.95;
    }
}

double AgentQLearning::calculateFutureReward(Field* nextState) {
    vector<int> availableMoves = getAvailableMoves(nextState);
    array<int,2> coordinates = nextState->getCoordinates();
    double reward;
    double highestReward = qTable[coordinates[0]][coordinates[1]][availableMoves[0]];
    for(int i = 1; i < availableMoves.size(); i++) {  
        reward = qTable[coordinates[0]][coordinates[1]][availableMoves[i]];
        if(reward > highestReward) {
            highestReward = reward;
        }
    }
    return highestReward;
}

void AgentQLearning::updateQTable(array<int,2> prevCoordinates, int move) {
    // Q(s,a) <- Q(s,a) + a *(R + y*max(Q(s', a)) - Q(s,a))
    Field* nextState = maze_->getField(getUpdatedCoordinates(prevCoordinates, move)); 
    qTable[prevCoordinates[0]][prevCoordinates[1]][move] += alpha*(getReward(nextState)
    +gamma*calculateFutureReward(nextState) - qTable[prevCoordinates[0]][prevCoordinates[1]][move]);
}
