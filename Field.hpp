#include<iostream>
#include<stdlib.h>
#include<random>

#pragma once

class Field
{
private:
    double reward;
public:
    Field();
    ~Field();
    double getReward() const;
};