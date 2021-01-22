#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(50,50);
    AgentDFS agentDFS = AgentDFS(maze, maze->getField({0,0}));
    agentDFS.DFS();
    maze->print();
    AgentSarsa agentSarsaEpsilon = AgentSarsa(maze, maze->getField({0,0}), 0);
    agentSarsaEpsilon.solveMaze();
    AgentSarsa agentSarsaBernoulli = AgentSarsa(maze, maze->getField({ 0,0 }), 1);
    agentSarsaBernoulli.solveMaze();
    AgentQLearning agentQLearningSarsa = AgentQLearning(maze, maze->getField({0,0}), 0);
    agentQLearningSarsa.solveMaze();
    AgentQLearning agentQLearningBernoulli = AgentQLearning(maze, maze->getField({ 0,0 }), 1);
    agentQLearningBernoulli.solveMaze();
    return 0;
}
