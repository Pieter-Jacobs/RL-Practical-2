#include "AgentQLearning.hpp"

using namespace std; 

AgentQLearning::AgentQLearning() {
}

AgentQLearning::AgentQLearning(Maze* maze, Field* currentField)
{
    maze_ = maze;
    currentField_ = currentField;

    for(int i=0; i < maze_->getHeight(); i++) {
        vector<vector<double>> row(maze_->getWidth(),{{0,0,0,0}}); 
        qTable.push_back(row);
    }
}

void AgentQLearning::solveMaze() {
    std::mt19937 gen(1729);
    uniform_real_distribution<double> dist(0,1);
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
            if (dist(gen) <= epsilon) {
                // explore
                // cout << "EXPLORE" << "\n";
                move_ = getRandomMove(availableMoves);
                // cout << "move" << move_ << "\n";
            }
            else {
                // exploit
                // cout << "EXPLOIT" << "\n"; 
                move_ = getQlearningMove(availableMoves);
                // cout << "move" << move_ << "\n";
            }
            //update the state action pair according to reward
            updateQTable(coordinates, move_);
            move(move_);
            steps++;
        }
        printQTable();
        epsilon *= 0.95;
    }
}

vector<int> AgentQLearning::getAvailableMoves(Field* state) { 
    vector<int> availableMoves; 
    array<int,4> obstacles = state->getWalls();
    for(int i = 0; i<4; i++) {
        if(obstacles[i] == 0) {
            availableMoves.push_back(i);
        }
    }
    return availableMoves;
}

void AgentQLearning::printQTable() {
    for(int i=0;i<maze_->getHeight();i++){
        for(int j=0;j<maze_->getWidth();j++){
            cout << "{";
            for(int k=0;k<4;k++){
                cout << qTable[i][j][k] << ",";
            }
            cout << "}";
        }
        cout << "\n";
    }
}
int AgentQLearning::getQlearningMove(vector<int> availableMoves) {
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

double AgentQLearning::getReward(Field* state) {
    if(state->isTerminalState()) {
        return 100;
    }
    return -1;
}

int AgentQLearning::getRandomMove(vector<int> availableMoves) {
    return availableMoves[rand()%availableMoves.size()];
}