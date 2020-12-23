#include<iostream>
#include<stdlib.h>
#include<vector>
#include<random>

#pragma once

class Field
{
private:
    double reward;
    int type;
    bool terminalState;
    // initilize all fields with walls against them
    std::vector<int> availableMoves{0,0,0,0};
public:
    Field();
    ~Field();
    double getReward() const;
    int getType() const;
    bool isTerminalState() const;
    std::vector<int> getAvailableMoves() const;
};