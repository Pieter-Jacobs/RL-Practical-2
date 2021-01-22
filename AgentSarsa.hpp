#include "AgentTemporal.hpp"

#pragma once; 
class AgentSarsa : public AgentTemporal 
{
    private:
    public:
        AgentSarsa();
        AgentSarsa(Maze* maze_, Field* currentfield, int algorithm);
        void solveMaze();
}
