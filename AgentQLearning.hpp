#include <random>
#include "Agent.hpp"


class AgentQLearning : public Agent
{
private:
    std::vector<std::vector<std::vector<double>>> qTable;
    size_t episodes = 10;
    double epsilon = 1;
    double gamma = 1;
    double alpha = 1;
    // /* data */
public:
    AgentQLearning(/* args */);
    AgentQLearning(Maze* maze, Field* currentField);
    std::array<int,2> getUpdatedCoordinates(std::array<int,2> coordinates, int move);
    std::vector<int> determinePossibleMoves();
    void solveMaze();
    void printQTable();
    std::vector<int> getAvailableMoves(Field* state);
    void updateQTable(std::array<int,2> prevCoordinates, int move);
    double getReward(Field* state);
    int getQlearningMove(std::vector<int> availableMoves);
    double calculateFutureReward(Field* nextState);
    int getRandomMove(std::vector<int> availableMoves);
};
