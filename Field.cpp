#include "Field.hpp"

using namespace std; 

double Field::getReward() const 
{
    cout << "Reward = " << reward << "\n";
    return reward;
};

int Field::getType() const 
{
    return type;
};

bool Field::isTerminalState() const
{
    return terminalState;
}

vector<int> Field::getAvailableMoves() const
{
    return availableMoves;
}

Field::Field()
{
    // uniform_int_distribution<double> urd(-1.0, 1.0);
    // cout << rand() << "\n";
    // default_random_engine e(rand());
    // reward = urd(e);
}

Field::~Field()
{
}
