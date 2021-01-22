#include "Agent.hpp"

class AgentTemporal : public Agent
{
protected:
    /* data */
    std::mt19937 g;
    std::uniform_real_distribution<double> d;
    std::vector<std::vector<std::vector<double>>> qTable;
    size_t episodes = 2;
    double epsilon = 1;
    double alpha = 0.8;
    double gamma = 1;
    int algorithm;
    int getRandomMove(std::vector<int> availableMoves);
    std::vector<int> getAvailableMoves(Field* state);
    int chooseActionEpsilonGreedy();
    int getQLearningMove(std::vector<int> availableMoves);
public:
    AgentTemporal(/* args */);
};
