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

int AgentTemporal::chooseAction(Field* state) {
    int move_; 
	switch (algorithm)
	{
	case 0:
		move_ = chooseActionEpsilonGreedy(state);
		break;
	case 1:
		move_ = chooseActionBoltzmann(state);
		break;
	}
    return move_;
}

int AgentTemporal::chooseActionEpsilonGreedy(Field* state) {
    if(d(g) <= epsilon) {
        return getRandomMove(getAvailableMoves(state));
    }
    return getQLearningMove(getAvailableMoves(state));
}

int AgentTemporal::chooseActionBoltzmann(Field* state) {
    vector<int> availableMoves = getAvailableMoves(state);
    array<int,2> coordinates = state->getCoordinates();
    array<double,4> probabilities = {0,0,0,0};
    double denominator = 0;
    double highestValue = qTable[coordinates[0]][coordinates[1]][availableMoves[0]]/temprature;
    for(int i = 1; i < availableMoves.size(); i++) {
        if(qTable[coordinates[0]][coordinates[1]][availableMoves[i]]/temprature > highestValue) {
            highestValue = qTable[coordinates[0]][coordinates[1]][availableMoves[i]]/temprature;
        }
    }
    for(int i = 0; i < availableMoves.size(); i++) {
        denominator += exp((qTable[coordinates[0]][coordinates[1]][availableMoves[i]]/temprature)
        - highestValue - 1);
    }
    for(int i = 0; i < availableMoves.size(); i++) {
        double numerator = exp((qTable[coordinates[0]][coordinates[1]][availableMoves[i]]/temprature)
        - highestValue - 1);
        probabilities[availableMoves[i]] = numerator/denominator;
    }

    double chance = d(g); 
    if(chance == 0) {
        chance += 0.001;
    }
    double sum = 0;
    for(int i = 0; i < 4; i++){
        sum += probabilities[i];
        if(chance <= sum) {
            return i;
        }
    }
    return NULL;
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

void AgentTemporal::printQTable() {
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

void AgentTemporal::saveResults(bool sarsa) {
    ofstream file;
    if (sarsa) {
        if (algorithm == 0)
            file.open("sarsaEpsilon.csv");
        if (algorithm == 1)
            file.open("sarsaBoltzmann.csv");
    }
    else {
        if (algorithm == 0)
            file.open("qLearningEpsilon.csv");
        if (algorithm == 1)
            file.open("qLearningBoltzmann.csv");
    }
    for (size_t i = 0; i != averageSteps.size(); ++i) {
        file << i << ',';
        file << averageSteps[i] << '\n';
    }
    file.close();
}