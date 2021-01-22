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
}

void AgentSarsa::solveMaze() {

    for(int i = 0; i < episodes; i++){
        while(!currentField_->isTerminalState()) {
            array<int,2> coordinates = currentField_->getCoordinates();
            int move_ = chooseAction();
            Field* newState = maze_->getField(getUpdatedCoordinates(coordinates,move));
            getReward(newState);

            //s=s'
            move(move_);
        }
    }
}

int AgentSarsa::chooseAction() {
    int move_; 
	switch (algorithm_)
	{
	case 0:
		move_ = chooseActionEpsilon();
		break;
	case 1:
		move_ = chooseActionBoltzmann();
		break;
	}
    return move_;
}
