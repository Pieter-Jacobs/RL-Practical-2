#include "Agent.hpp"

class AgentDFS : public Agent
{
private:
    std::vector<Field*> visited;
public:
    AgentDFS();
    AgentDFS(Maze* maze, Field* currentField);
    std::vector<int> getAvailableMoves();
    void DFS();
};