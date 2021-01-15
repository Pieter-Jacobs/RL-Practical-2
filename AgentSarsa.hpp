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
    Field* state_;          //s
    Field* newState_;
    Maze* maze_;
    double score;           
    int action_;          //a
    int newAction_;
    double totalReward;
    double reward_;          //R
    double alpha;           //stepsize
    double gamma;           //stepsize
    size_t episode;
    double epsilon;

    void chooseActionEpsilon(bool newAction);
    void chooseActionBoltzmann(bool newAction);
    void takeAction();
    void updateValue();

public:
    AgentSarsa();
    AgentSarsa(Maze* maze_, size_t episode);
    void Sarsa();

};
