#include "AgentSarsa.hpp"

using namespace std;

AgentSarsa::AgentSarsa()
{
	AgentSarsa::score= 0;
}

AgentSarsa::AgentSarsa(Maze* maze_, size_t episodeMax) 
{
	AgentSarsa::maze_ = maze_;
	AgentSarsa::score = 0;
	AgentSarsa::episodeMax = episodeMax;
	AgentSarsa::gamma = 1;
	AgentSarsa::alpha = 0.5;
	AgentSarsa::epsilon = 1.0;
	AgentSarsa::episode = 0.99;
	AgentSarsa::temp = 10.0;						//1.0 werkt goed voor 10x10, 10.0 voor 100x100, onder 1.0 komen problemen en soms met 1.0 bij 100x100
	AgentSarsa::randomCount = 0;
}

void AgentSarsa::Sarsa()
{
	for (episode = 1; episode != episodeMax + 1; ++episode) {							//for each episode
		state_ = maze_->getField({ 0,0 });							//initialize S
		size_t step = 0;
		chooseActionEpsilon(false);								//choose action from state based on policy
		randomCount = 0;
		while (!state_->isTerminalState()) {
			takeAction();											//take the action that was chosen, keep track of new state and reward
			chooseActionEpsilon(true);							//choose new action from new state based on policy
			updateValue();											//update old state-action pair based on stepsizes and new state-action pair
			state_ = newState_;
			action_ = newAction_;
			++step;
			if(state_ == maze_->getField({ 0,0 }))
				break;
		}
		epsilon = 1.0 - 0.01 * episode;
		if (epsilon < 0)
			epsilon = 0;

		if (temp != 1)
			temp -= 0.1;

		if (state_->isTerminalState())
			cout << "End reached!\n";
		cout << "Amount of steps: " << step << '\n';
		//cout << "Amount of random steps: " << randomCount << '\n';		//The amount of steps the epsilon greedy algorithm explored
	}
}

void AgentSarsa::chooseActionEpsilon(bool newAction)		//the exploration strategy
{
	double highestAction = -100000000;
	double actionValue = 0;

	size_t actionNumber = 0;
	std::array<double, 4> actionList = newAction ? newState_->getActions() : state_->getActions();
	double randomNumber = (double)rand() / RAND_MAX;				//number between 0 and 1

	if (randomNumber <= epsilon) {				//epsilon Greedy
		size_t i = rand() % 4;
		actionNumber = i;
		++randomCount;
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
	for (size_t i = 0; i != 4; ++i) {						//calculate the probabilities
		double numerator = exp(actionList[i] / temp);		//e^(Q(s,a)/T)
		double denominator = 0;
		for (size_t j = 0; j != 4; ++j) {
			denominator += exp(actionList[j] / temp);
		}
		/*if (denominator == 0) {									// Hiermee kan je de Q(s,a) zien wanneer het mis gaat
			cout << "Numerator: " << numerator << '\n';
			cout << "Denominator: " << denominator << '\n';
			cout << "Temperature: " << temp << '\n';
			for (size_t j = 0; j != 4; ++j) {
				cout << actionList[j] << '\n';
			}
		}*/
		probabilities[i] = numerator / denominator;

	}
	double randomNumber = (double) rand() / RAND_MAX;				//number between 0 and 1
	size_t actionNumber = 0;
	if (randomNumber < probabilities[0]) {
		actionNumber = 0;
	} else if(randomNumber < probabilities[0] + probabilities[1]) {
		actionNumber = 1;
	}
	else if (randomNumber < probabilities[0] + probabilities[1] + probabilities[2]) {
		actionNumber = 2;
	}
	else {
		actionNumber = 3;
	}

	if (newAction) {
		newAction_ = actionNumber;
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
		if(!state_->getWalls()[0])
			coordinates[0] -= 1;
		break;
		// move right
	case 1:
		if (!state_->getWalls()[1])
			coordinates[1] += 1;
		break;
		// move down
	case 2:
		if (!state_->getWalls()[2])
			coordinates[0] += 1;
		break;
		// move left
	case 3:
		if (!state_->getWalls()[3])
			coordinates[1] -= 1;
		break;
	default:
		break;
	}
	newState_ = maze_->getField(coordinates);
	reward_ = newState_->getReward();

	if (newState_ == state_) {
		newState_ = maze_->getField({ 0,0 });
		reward_ = -5;
	}
	
		
}

void AgentSarsa::updateValue()
{
	array<double, 4> oldActions = state_->getActions();
	array<double, 4> newActions = newState_->getActions();
	double newValue = oldActions[action_] + alpha * (reward_ + gamma * newActions[newAction_] - oldActions[action_]);
	state_->updateAction(action_, newValue);
}