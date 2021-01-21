#include "AgentDFS.hpp"

using namespace std;

AgentDFS::AgentDFS(){}

AgentDFS::AgentDFS(Maze* maze, Field* currentField)
{
    maze_ = maze;
    currentField_ = currentField;
}

vector<int> AgentDFS::getAvailableMoves() {
    vector<int> possibleMoves;
    // Check what neighbouring fields can be moved to 
    for(int i = 0; i < 4; i++) {
        // if the new field is not visited yet and the move does not get the agent
        // outside of the grid, the move is possible
        if(currentField_->getWalls()[i] != -1 &&
        (find(visited.begin(), visited.end(), maze_->getField(getUpdatedCoordinates(i))) 
        == visited.end())) {
            cout << "move possible:" << i << "\n";
            possibleMoves.push_back(i);
        }
    }
    return possibleMoves;
}

void AgentDFS::DFS() 
{
    // Initial field is marked as visited and pushed to the stack
    stack<Field*> stack;
    visited.push_back(currentField_);
    stack.push(currentField_);
    while (!stack.empty())
    {
        // Make the top field on the stack the current field
        currentField_ = stack.top();
        stack.pop();
        array<int,2> coordinates = currentField_->getCoordinates();
        vector<int> possibleMoves = getAvailableMoves();
        // If any moves can be made, we push the field to the stack
        // and move to a random neighbour
        if(!possibleMoves.empty()) {
            stack.push(currentField_);
            int move_ = possibleMoves[rand()%possibleMoves.size()];
            // Remove the wall on the field the agent is moving to
            currentField_->removeWall(move_);
            maze_->getField(getUpdatedCoordinates(move_))->removeWall((move_+2)%4);
            // maze_->getField(getUpdatedCoordinates(move_))->removeWall();
            
            cout << "move: " << move_ << "\n";
            // Move to the neighbour and mark it as visited and push it to the stack
            move(move_);
            visited.push_back(currentField_);
            stack.push(currentField_);
        }
    }    
}