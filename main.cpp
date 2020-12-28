#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(3,3);
    Agent agent = Agent(maze, maze->getField({0,0}));
    agent.DFS();
    maze->print();
    return 0;
}
