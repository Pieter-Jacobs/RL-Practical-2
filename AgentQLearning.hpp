#include <random>
#include "AgentTemporal.hpp"

#pragma once
class AgentQLearning : public AgentTemporal
{
private:
    // /* data */
    void printQTable();
    void updateQTable(std::array<int,2> prevCoordinates, int move);
    int getQlearningMove(std::vector<int> availableMoves);
    double calculateFutureReward(Field* nextState);
public:
    AgentQLearning(/* args */);
    AgentQLearning(Maze* maze, Field* currentField);
    void solveMaze();
};
