#include<iostream>
#include<stdlib.h>
#include<random>

#pragma once

class Field
{
private:
    double reward;
    int type;
    bool terminalState;
    int availableMoves[4];
public:
    Field();
    ~Field();
    double getReward() const;
    int getType() const;
    bool isTerminalState() const;
    int * getAvailableMoves() const;
};