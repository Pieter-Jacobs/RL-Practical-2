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
    std::array<double, 4> actions_;             //The Q-values
    double reward = -1;                         //Every field has a reward of -1, except for the terminal state
    bool terminalState = false;
public:
    Field(std::array<int, 2> coordinates, size_t mazeWidth, size_t mazeHeight);
    ~Field();
    std::array<int, 2> getCoordinates() const;
    std::array<int, 4> getWalls() const;
    std::array<double, 4> Field::getActions();
    void updateAction(int action, double value); //Update the Q-value of the specified action
    double getReward() const;
    bool isTerminalState() const;
    void removeWall(int move);
    void printActions();
};