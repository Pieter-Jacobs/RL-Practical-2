#include "AgentSarsa.hpp"

using namespace std;

AgentSarsa::AgentSarsa()
{
}

AgentSarsa::AgentSarsa(Maze* maze, size_t episodeMax, size_t algorithm, double alpha)		//Some hyperparameters can be changed here
	: maze_(maze), episodeMax_(episodeMax), gamma(1), alpha(alpha), epsilon(0.5), episode(1), temp(1.5), algorithm_(algorithm), averageSteps(0)
{
}

void AgentSarsa::Sarsa()
{
	size_t step = 0;
	for (episode = 1; episode != episodeMax_ + 1; ++episode) {							//for each episode
		step = 0;
		state_ = maze_->getField({ 0,0 });							//initialize S
		chooseAction(false);										//choose action from state based on policy
		while (!state_->isTerminalState()) {
			takeAction();											//take the action that was chosen, keep track of new state and reward
			chooseAction(true);										//choose new action from new state based on policy
			updateValue();											//update old state-action pair based on the update formula
			state_ = newState_;
			action_ = newAction_;
			++step;
		}
		
		if (algorithm_ == 0) {										//Decrease epsilon each episode if the chosen algorithm is epsilon greedy
			epsilon = 0.5 - 0.01 * episode;
			if (epsilon < 0)
				epsilon = 0;
		}
		else if (algorithm_ == 1) {									//Decrease temperature each episode if the chosen algorithm is boltzmann exploration
			temp = 1.5 - 0.01 * episode;
			if (temp < 0.01)
				temp = 0.01;
		}
		cout << "Amount of steps: " << step << '\n';
		averageSteps += step;
	}
	finalSteps = step;
	averageSteps /= episodeMax_;
}

void AgentSarsa::chooseAction(bool newAction)				//Choose action based on the chosen exploration strategy
{
	switch (algorithm_)
	{
	case 0:
		chooseActionEpsilon(newAction);
		break;
	case 1:
		chooseActionBoltzmann(newAction);
		break;
	case 2:
		chooseActionEpsilon(newAction);		//This will be UCB
		break;
	}
}

void AgentSarsa::chooseActionEpsilon(bool newAction)		//epsilon-greedy
{
	double highestAction = -100000000;								//initialize low
	double actionValue = 0;

	size_t actionNumber = 0;
	Field* actionState = newAction ? newState_ : state_;			//state the action is taken from
	std::array<double, 4> actionList = actionState->getActions();   //get the list of  Q-values of the state
	std::array<int, 4> wallList = actionState->getWalls();			//get the list of walls of the state
	double randomNumber = (double)rand() / RAND_MAX;				//number between 0 and 1
	while (randomNumber == 0 || randomNumber == 1)					//make sure it is not 0 or 1
		randomNumber = (double)rand() / RAND_MAX;

	if (randomNumber <= epsilon) {									//epsilon Greedy
		size_t i = rand() % 4;										//choose random action
		while (wallList[i] != 0)									//till action is not a wall
			i = rand() % 4;

		actionNumber = i;
	}
	else
	{
		for (size_t i = 0; i != 4; ++i) {							//Find the highest action
			actionValue = actionList[i];
			if (actionValue == highestAction) {
				if (rand() % 2 && wallList[i] == 0) {				//50% chance to switch if the Q-values of 2 actions are the same
					actionNumber = i;
				}
			}
			if (actionValue > highestAction && wallList[i] == 0) {	//Highest valued action should not be a wall
				highestAction = actionValue;
				actionNumber = i;
			}
		}
	}

	if (newAction) {												//set the correct variable
		newAction_ = actionNumber;
	} else {
		action_ = actionNumber;
	}
}

void AgentSarsa::chooseActionBoltzmann(bool newAction)		//Boltzmann Exploration
{
	std::array<double, 4> probabilities = { };								//List of the probabilities
	Field* actionState = newAction ? newState_ : state_;					//state the action is taken from
	std::array<double, 4> actionList = actionState->getActions();			//get the list of  Q-values of the state
	std::array<int, 4> wallList = actionState->getWalls();					//get the list of walls of the state
	double max = -100000000000;												//initialize low
	for (size_t i = 0; i != 4; ++i) {										//find the maximum of the Q-values (Used for normalizing later)
		if (((actionList[i] / temp) > max && wallList[i] == 0))				//Should not be a wall
			max = actionList[i] / temp;
	}
	for (size_t i = 0; i != 4; ++i) {										//calculate the probabilities
		if (wallList[i] == 0) {												//Walls are not calculated
			double numerator = exp((actionList[i] / temp) - max - 1);		//e^(Q(s,a)/T), normalized to prevent underflow, -1 to prevent it from being 0
			double denominator = 0;
			for (size_t j = 0; j != 4; ++j) {								//calculate the denominator, again normalized
				if(wallList[j] == 0)										//Walls are skipped
					denominator += exp((actionList[j] / temp) - max - 1);
			}
			probabilities[i] = numerator / denominator;
		}
		else {																//Walls get a probability of 0
			probabilities[i] = 0;	
		}

	}
	double randomNumber = (double) rand() / RAND_MAX;						//number between 0 and 1
	while (randomNumber == 0 || randomNumber == 1)							//make sure it is not 0 or 1
		randomNumber = (double)rand() / RAND_MAX;

	size_t actionNumber = 0;
	if (randomNumber <= probabilities[0]) {									//Choose an action based on the probabilities
		actionNumber = 0;
	} 
	else if (randomNumber <= probabilities[0] + probabilities[1]) {
		actionNumber = 1;
	}
	else if (randomNumber <= probabilities[0] + probabilities[1] + probabilities[2]) {
		actionNumber = 2;
	}
	else {																	//This should add up to 1.0
		actionNumber = 3;
	}

	if (newAction) {														//set the correct variable
		newAction_ = actionNumber;
	} else {
		action_ = actionNumber;
	}
}

void AgentSarsa::takeAction()												//Take the specified action
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

void AgentSarsa::updateValue()										//update the Q-value of the chosen state-action pair
{
	array<double, 4> oldActions = state_->getActions();
	array<double, 4> newActions = newState_->getActions();
	double newValue = oldActions[action_] + alpha * (reward_ + gamma * newActions[newAction_] - oldActions[action_]);
	state_->updateAction(action_, newValue);
}

void AgentSarsa::printData()										//print the data
{
	cout << "Amount of steps in the last run: " << finalSteps << '\n';
	cout << "Average amount of steps: " << averageSteps << '\n';
}