#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(11,11);
    Agent agent = Agent(maze, maze->getField({0,0}));
    agent.DFS();
    AgentSarsa sarsa = AgentSarsa(maze, 8000);
    maze->print();
    sarsa.Sarsa();
    //maze->printActions();
    return 0;
}
