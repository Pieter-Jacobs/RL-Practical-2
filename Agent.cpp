#include "Agent.hpp"

using namespace std;

Agent::Agent()
{
}

Agent::Agent(Maze* maze, Field* currentField)
    :  maze_(maze), currentField_(currentField)
{
}

Agent::~Agent()
{
}

array<int,2> Agent::getUpdatedCoordinates(int move) {
    array<int, 2> coordinates = currentField_->getCoordinates();
    switch (move)
    {
        // move up
        case 0:
            coordinates[0] -= 1;
            break;
        // move right
        case 1:
            coordinates[1] += 1;
            break;
        // move down
        case 2: 
            coordinates[0] += 1;
            break;
        // move left
        case 3: 
            coordinates[1] -= 1;
            break;
        default:
            break;
    }
    return coordinates;
}

void Agent::DFS() 
{
    // Initial field is marked as visited and pushed to the stack
    vector<Field*> visited;
    stack<Field*> stack;
    vector<int> possibleMoves;
    visited.push_back(currentField_);
    stack.push(currentField_);
    while (!stack.empty() && !currentField_->isTerminalState())
    {
        // Make the top field on the stack the current field
        currentField_ = stack.top();
        cout << currentField_->getCoordinates()[0] << " " << currentField_->getCoordinates()[1] << "\n";
        stack.pop();

        array<int,2> coordinates = currentField_->getCoordinates();
        // Check what neighbouring fields can be moved to 
        for(int i = 0; i < 4; i++) {
            // if the new field is not visited yet and the move does not get the agent
            // outside of the grid, the move is possible
            if(currentField_->getWalls()[i] != -1
            /*!isOutOfBounds(getUpdatedCoordinates(i)) */ &&
            (find(visited.begin(), visited.end(), maze_->getField(getUpdatedCoordinates(i))) 
            == visited.end())) {
                cout << "move possible:" << i << "\n";
                possibleMoves.push_back(i);
            }
        }
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
            possibleMoves.clear();
        }
    }    
}

bool Agent::isOutOfBounds(array<int,2> coordinates) {
    if(coordinates[0] >= 0 && coordinates[0] < maze_->getHeight() 
    && coordinates[1] >= 0 && coordinates[1] < maze_->getWidth()){
        return 0;
    }
    return 1;
}

void Agent::move(int move)
{
    array<int, 2> coordinates = getUpdatedCoordinates(move);   
    cout << "moved to: " << coordinates[0] << " " << coordinates[1] << "\n";
    currentField_ = maze_->getField(coordinates);
}
