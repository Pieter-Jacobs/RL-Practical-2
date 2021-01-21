#include "Agent.hpp"

class AgentDFS : public Agent
{
private:
    std::vector<Field*> visited;
    std::vector<int> getAvailableMoves();
public:
    AgentDFS();
    AgentDFS(Maze* maze, Field* currentField);
    void DFS();
};