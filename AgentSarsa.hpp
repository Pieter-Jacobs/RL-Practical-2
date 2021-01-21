#include "Maze.hpp"
#include "Field.hpp"
#include<stack>
#include<vector>
#include<array>
#include<iostream>

#pragma once 

class AgentSarsa            //Q(s,a) <- Q(s,a) + alpha [R + gamma Q(s',a') - Q(s,a)]
{
private:
    Field* state_;          //The current state of the agent
    Field* newState_;       //The new state of the agent
    Maze* maze_;            //The maze
    int action_;            //The action that the agent chose (state_ + action_ -> newState_)
    int newAction_;         //The action that the agent chose from the new state
    double reward_;         //The reward that was obtained from the new state
    double alpha;           //Learning rate
    double gamma;           //Discount Factor
    size_t episode;         //Current Episode
    size_t episodeMax_;     //Maximum amount of episode
    double epsilon;         //Epsilon for epsilon-greedy
    double temp;            //temperature for boltzmann exploration
    int algorithm_;         //0 is epsilon greedy, 1 is boltzmann exploration, 2 is UCB
    double averageSteps;    //Average amount of steps the agent takes to find the exit
    size_t finalSteps;      //Amount of steps the agent took in the final episode

    void chooseActionEpsilon(bool newAction);       //Choose an action using epsilon-greedy
    void chooseActionBoltzmann(bool newAction);     //Choose an action using boltzmann exploration
    void takeAction();                              //Take the chosen action and generate its reward
    void updateValue();                             //Update the Q-value of the chosen state-action pair
    void chooseAction(bool newAction);              //Choose an action using the specified algorithm

public:
    AgentSarsa();
    AgentSarsa(Maze* maze_, size_t episodeMax, size_t algorithm, double alpha);
    void Sarsa();
    void printData();
};
