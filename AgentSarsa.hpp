#include "Agent.hpp"

class AgentSarsa : public Agent 
{
    private:
    
    public:
        AgentSarsa();
        AgentSarsa(Maze* maze_, size_t episodeMax, size_t algorithm, double alpha);
}
