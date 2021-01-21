#include "main.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    Maze* maze = new Maze(100,100);
    Agent agent = Agent(maze, maze->getField({0,0}));
    agent.DFS();
    AgentSarsa sarsaEpsilon0 = AgentSarsa(maze, 8000, 0, 0.98);         //Useful when optimizing hyperparameters
    AgentSarsa sarsaEpsilon1 = AgentSarsa(maze, 8000, 0, 0.97);
    AgentSarsa sarsaEpsilon2 = AgentSarsa(maze, 8000, 0, 0.96);
    AgentSarsa sarsaEpsilon3 = AgentSarsa(maze, 8000, 0, 0.95);
    AgentSarsa sarsaBoltzmann0 = AgentSarsa(maze, 8000, 1, 0.99);
    AgentSarsa sarsaBoltzmann1 = AgentSarsa(maze, 8000, 1, 0.98);
    AgentSarsa sarsaBoltzmann2 = AgentSarsa(maze, 8000, 1, 0.97);
    AgentSarsa sarsaBoltzmann3 = AgentSarsa(maze, 8000, 1, 0.96);

    sarsaEpsilon0.Sarsa();
    maze->resetActions();
    sarsaEpsilon1.Sarsa();
    maze->resetActions();
    sarsaEpsilon2.Sarsa();
    maze->resetActions();
    sarsaEpsilon3.Sarsa();
    maze->resetActions();

    sarsaBoltzmann0.Sarsa();
    maze->resetActions();
    sarsaBoltzmann1.Sarsa();
    maze->resetActions();
    sarsaBoltzmann2.Sarsa();
    maze->resetActions();
    sarsaBoltzmann3.Sarsa();
    maze->resetActions();

    cout << "Data for EpsilonGreedy: \n";
    sarsaEpsilon0.printData();
    sarsaEpsilon1.printData();
    sarsaEpsilon2.printData();
    sarsaEpsilon3.printData();
    cout << "Data for Boltzmann Exploration: \n";
    sarsaBoltzmann0.printData();
    sarsaBoltzmann1.printData();
    sarsaBoltzmann2.printData();
    sarsaBoltzmann3.printData();
    agent.printOptimalSteps();
    return 0;
}
