#include "AgentSarsa.hpp"

using namespace std;

AgentSarsa::AgentSarsa()
{
	AgentSarsa::score= 0;
}

AgentSarsa::AgentSarsa(Maze* maze_, size_t episode) 
{
	AgentSarsa::maze_ = maze_;
	AgentSarsa::score = 0;
	AgentSarsa::episode = episode;
	AgentSarsa::gamma = 1;
	AgentSarsa::alpha = 0.5;
	AgentSarsa::epsilon = 0.1;
}

void AgentSarsa::Sarsa()
{
	for (size_t i = 0; i != episode; ++i) {							//for each episode
		state_ = maze_->getField({ 0,0 });							//initialize S
		state_->initializeActions();
		size_t step = 0;
		chooseActionBoltzmann(false);										//choose action from state based on policy
		while (!state_->isTerminalState()) {						//for each step
			takeAction();											//take the action that was chosen, keep track of new state and reward
			newState_->initializeActions();							//make sure all the walls are -100
			chooseActionBoltzmann(true);										//choose new action from new state based on policy
			updateValue();											//update old state-action pair based on stepsizes and new state-action pair
			state_ = newState_;
			action_ = newAction_;
			++step;
		}
		cout << "Amount of steps:" << step << '\n';
	}
}

void AgentSarsa::chooseActionEpsilon(bool newAction)		//the exploration strategy
{
	double highestAction = -99;
	double actionValue = 0;

	size_t actionNumber = 0;
	size_t chance = 1 / epsilon;

	std::array<double, 4> actionList = newAction ? newState_->getActions() : state_->getActions();
	if (rand() % chance == 0) {				//epsilon Greedy
		size_t i = rand() % 4;
		while (actionList[i] == -100) {
			i = rand() % 4;
		}
		actionNumber = i;
	}
	else
	{
		for (size_t i = 0; i != 4; ++i) {
			actionValue = actionList[i];
			if (actionValue == highestAction) {
				if (rand() % 2) {
					actionNumber = i;
				}
			}
			if (actionValue > highestAction) {
				highestAction = actionValue;
				actionNumber = i;
			}
		}
	}
	if (newAction) {
		newAction_ = actionNumber;
	} else {
		action_ = actionNumber;
	}
}

void AgentSarsa::chooseActionBoltzmann(bool newAction)
{
	std::array<double, 4> probabilities = { };
	std::array<double, 4> actionList = newAction ? newState_->getActions() : state_->getActions();
	double temp = 0.5;
	for (size_t i = 0; i != 4; ++i) {						//calculate the probabilities
		if (actionList[i] == -100) {
			probabilities[i] = 0;
		}
		else {
			double numerator = exp(actionList[i] / temp);		//e^(Q(s,a)/T)
			double denominator = 0;
			for (size_t j = 0; j != 4; ++j) {
				if (actionList[j] != -100)
					denominator += exp(actionList[j] / temp);
			}
			probabilities[i] = numerator / denominator;
		}
	}
	double randomNumber = rand() % 1000 + 1;				//number between 1 and 1000
	double check = 0;
	size_t actionNumber = 0;
	for (actionNumber = 0; actionNumber != 4; ++actionNumber) {
		check += probabilities[actionNumber] * 1000;
		if (check > randomNumber)
			break;
	}

	if (actionNumber == 4){
		for (size_t i = 3; i != 0; i--) {
			if (probabilities[i] != 0) {
				actionNumber = i;
				break;
			}
		}
	}

	if (newAction) {
		newAction_ = actionNumber;
		//cout << probabilities[newAction_] << '\n';
	} else {
		action_ = actionNumber;
	}
}

void AgentSarsa::takeAction()
{
	array<int, 2> coordinates = state_->getCoordinates();
	switch (action_)
	{
		// move up
	case 0:
		coordinates[0] -= 1;
		break;
		// move right
	case 1:
		coordinates[1] += 1;
		break;
		// move down
	case 2:
		coordinates[0] += 1;
		break;
		// move left
	case 3:
		coordinates[1] -= 1;
		break;
	default:
		break;
	}
	newState_ = maze_->getField(coordinates);
	reward_ = newState_->getReward();
}

void AgentSarsa::updateValue()
{
	array<double, 4> oldActions = state_->getActions();
	array<double, 4> newActions = newState_->getActions();
	double newValue = oldActions[action_] + alpha * (reward_ + gamma * newActions[newAction_] - oldActions[action_]);
	state_->updateAction(action_, newValue);
}