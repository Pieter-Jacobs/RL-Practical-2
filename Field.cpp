#include "Field.hpp"

using namespace std; 

double Field::getReward() const 
{
    cout << "Reward = " << reward << "\n";
    return reward;
};

Field::Field()
{
    uniform_real_distribution<double> urd(0.0, 5.0);
    cout << rand() << "\n";
    default_random_engine e(rand());
    reward = urd(e);
}

Field::~Field()
{
}
