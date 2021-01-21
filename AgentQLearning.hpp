#include <random>
#include "Agent.hpp"


class AgentQLearning : public Agent
{
private:
    std::vector<std::vector<std::vector<double>>> qTable;
    size_t episodes = 100;
    double epsilon = 1;
    double gamma = 1;
    double alpha = 1;
    // /* data */
    void printQTable();
    void updateQTable(std::array<int,2> prevCoordinates, int move);
    int getQlearningMove(std::vector<int> availableMoves);
    int getRandomMove(std::vector<int> availableMoves);
    double getReward(Field* state);
    double calculateFutureReward(Field* nextState);
    std::vector<int> getAvailableMoves(Field* state);
public:
    AgentQLearning(/* args */);
    AgentQLearning(Maze* maze, Field* currentField);
    void solveMaze();
};
