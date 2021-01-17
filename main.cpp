#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(300,300);
    Agent agent = Agent(maze, maze->getField({0,0}));
    agent.DFS();
    maze->print();
    AgentSarsa sarsa = AgentSarsa(maze, 8000);
    sarsa.Sarsa();
    agent.printOptimalSteps();
    return 0;
}
