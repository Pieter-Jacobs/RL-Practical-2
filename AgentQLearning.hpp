#include <random>
#include "Agent.hpp";


class AgentQLearning : public Agent
{
private:
    std::vector<std::vector<std::vector<double>>> qTable;
    double epsilon = 1;
    double gamma;
    double alpha;
    // /* data */
public:
    AgentQLearning(/* args */);
    ~AgentQLearning();
    std::vector<int> determinePossibleMoves();
    void solveMaze();
    void selectAction();
    void updateQTable(int move);
    double calculateQValue(int move, Field* state);
};
