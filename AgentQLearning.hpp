#include "Agent.hpp";


class AgentQLearning : public Agent
{
private:
    std::vector<std::vector<std::vector<double>>> qTable;
    double gamma;
    // /* data */
public:
    AgentQLearning(/* args */);
    ~AgentQLearning();
    std::vector<int> determinePossibleMoves();
    void selectAction();
    void updateQTable();
    double calculateQValue(int move, Field* state);
};
