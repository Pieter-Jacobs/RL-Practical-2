#include<iostream>
#include<stdlib.h>
#include<random>
#include<array>

#pragma once

class Field
{
private:
    std::array<int, 2> coordinates_;
    // initilize all fields with walls against them
    std::array<int, 4> availableMoves;
    double reward;
    bool terminalState;
public:
    Field(std::array<int, 2> coordinates);
    ~Field();
    std::array<int, 2> getCoordinates() const;
    std::array<int, 4> getAvailableMoves(bool dfs) const;
    double getReward() const;
    bool isTerminalState() const;
    void removeWall(int wall);
};