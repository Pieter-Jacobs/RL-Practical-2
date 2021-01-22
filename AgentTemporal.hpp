#include "Agent.hpp"
#include <iostream>
#include <fstream>

#pragma once

class AgentTemporal : public Agent
{
protected:
    /* data */
    std::mt19937 g;
    std::uniform_real_distribution<double> d;
    std::vector<std::vector<std::vector<double>>> qTable;
    size_t episodes = 1000;
    double epsilon = 1;
    double alpha = 0.8;
    double gamma = 1;
    double temprature = 1.5;
    int algorithm = 1;
    std::vector<double> averageSteps;
    int getRandomMove(std::vector<int> availableMoves);
    std::vector<int> getAvailableMoves(Field* state);
    int chooseAction(Field* state);
    int chooseActionEpsilonGreedy(Field* state);
    int chooseActionBoltzmann(Field* state);
    int getQLearningMove(std::vector<int> availableMoves);
    void printQTable();
    void saveResults(bool sarsa);
public:
    AgentTemporal(/* args */);
};
