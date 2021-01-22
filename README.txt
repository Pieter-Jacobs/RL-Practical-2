To compile and run this code from the command line, the visual studio 
cmd can be used with the following commands:
Compiling: cl /EHsc main.cpp Maze.cpp Field.cpp Agent.cpp AgentDFS.cpp AgentSarsa.cpp AgentQLearning.cpp
Run: main
(https://docs.microsoft.com/en-us/cpp/build/walkthrough-compiling-a-native-cpp-program-on-the-command-line?view=msvc-160)

Before plotting the results with plot.py, the user needs to:
1. Run algorithm 0 through 4 with a Gaussian distribution
2. Run algorithm 0 through 4 with a Bernoulli distribution
3. run "python plot.py"