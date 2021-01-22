#include "AgentTemporal.hpp"

#pragma once

class AgentSarsa : public AgentTemporal 
{
    private:
        void updateQTable(std::array<int,2> prevCoordinates, int move);
    public:
        AgentSarsa();
        AgentSarsa(Maze* maze_, Field* currentfield);
        void solveMaze();
};
