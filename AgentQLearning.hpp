#include <random>
#include "AgentTemporal.hpp"

#pragma once
class AgentQLearning : public AgentTemporal
{
private:
    // /* data */
    void updateQTable(std::array<int,2> prevCoordinates, int move);
    double calculateFutureReward(Field* nextState);
public:
    AgentQLearning(/* args */);
    AgentQLearning(Maze* maze, Field* currentField, int number);
    void solveMaze();
};
