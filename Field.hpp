#pragma once

#include<iostream>
#include<stdlib.h>
#include<random>
#include<array>

class Field
{
private:
    std::array<int, 2> coordinates_;
    // initilize all fields with walls against them
    std::array<int, 4> walls;
    double reward;
    bool terminalState = false;
public:
    Field(std::array<int, 2> coordinates, size_t mazeWidth, size_t mazeHeight);
    ~Field();
    std::array<int, 2> getCoordinates() const;
    std::array<int, 4> getWalls() const;
    double getReward() const;
    bool isTerminalState() const;
    void removeWall(int move);
};