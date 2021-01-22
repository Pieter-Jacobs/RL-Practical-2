#include "AgentSarsa.hpp"

using namespace std;

AgentSarsa::AgentSarsa(){

}

AgentSarsa::AgentSarsa(Maze* maze, Field* currentField){
    maze_ = maze;
    currentField_ = currentField_;
    mt19937 gen(1729);
    uniform_real_distribution<double> dist(0,1);
    g = gen;
    d = dist;

    
    for(int i=0; i < maze_->getHeight(); i++) {
        vector<vector<double>> row(maze_->getWidth(),{{0,0,0,0}}); 
        qTable.push_back(row);
    }
}

void AgentSarsa::solveMaze() {
    int steps = 0;
    for(int i = 0; i < episodes; i++){
        // set agent back to starting field
        currentField_ = maze_->getField({0,0});
        cout << steps << "\n";
        steps = 0;
        cout << i << "\n";
        while(!currentField_->isTerminalState()) {
            array<int,2> coordinates = currentField_->getCoordinates();
            int move_ = chooseAction(currentField_);
            updateQTable(coordinates,move_);
            //s=s'
            move(move_);
            steps++;
        }
        if(algorithm == 0) {
            epsilon *= 0.95;
        }
    }
    printQTable();
}

int AgentSarsa::chooseAction(Field* state) {
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

void AgentSarsa::updateQTable(array<int,2> prevCoordinates, int move) {
    Field* nextState = maze_->getField(getUpdatedCoordinates(prevCoordinates,move));
    array<int,2> newCoordinates = nextState->getCoordinates();
    qTable[prevCoordinates[0]][prevCoordinates[1]][move] += alpha*(getReward(nextState)
    + gamma* qTable[newCoordinates[0]][newCoordinates[1]][chooseAction(nextState)] - qTable[prevCoordinates[0]][prevCoordinates[1]][move]);
}