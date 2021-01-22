#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(11,11);
    AgentDFS agentDFS = AgentDFS(maze, maze->getField({0,0}));
    agentDFS.DFS();
    maze->print();
    AgentSarsa agentSarsa = AgentSarsa(maze, maze->getField({0,0}));
    agentSarsa.solveMaze();
    AgentQLearning agentQLearning = AgentQLearning(maze, maze->getField({0,0}));
    agentQLearning.solveMaze();
    return 0;
}
