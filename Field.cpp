#include "Field.hpp"

using namespace std; 

double Field::getReward() const 
{
    cout << "Reward = " << reward << "\n";
    return reward;
};

bool Field::isTerminalState() const
{
    return terminalState;
}

array<int, 4> Field::getAvailableMoves(bool dfs) const
{
    if(dfs) { 
        return {1,1,1,1}
    }
    return availableMoves;
}

array<int, 2> Field::getCoordinates() const
{   
    return coordinates_;
}

void Field::removeWall(int wall)
{
    availableMoves[wall] = 1;
}

Field::Field(array<int, 2> coordinates)
    : coordinates_(coordinates), availableMoves({0,0,0,0})
{
    // uniform_int_distribution<double> urd(-1.0, 1.0);
    // cout << rand() << "\n";
    // default_random_engine e(rand());
    // reward = urd(e);
}

Field::~Field()
{
}
