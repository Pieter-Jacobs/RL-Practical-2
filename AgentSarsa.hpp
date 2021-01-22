#include "AgentTemporal.hpp"

#pragma once; 
class AgentSarsa : public AgentTemporal 
{
    private:
        void updateQTable(array<int,2> prevCoordinates, int move);
        int chooseAction(Field* state);
    public:
        AgentSarsa();
        AgentSarsa(Maze* maze_, Field* currentfield);
        void solveMaze();
};
