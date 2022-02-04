#include <cstddef> // needed for NULL on newer compilers
#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"

// Constructors

Maze::Maze(){ // Allows the creation of an empty maze
    this->start = nullptr;
    this->target = nullptr;
    this->current = nullptr;
    this->previous = nullptr;
}

Maze::Maze(fstream& filestream){
    string line;
    Cell* tempCell = nullptr;
    while (!filestream.eof()){ // Generate maze line by line
        getline(filestream, line);
        tempCell = insertCellRow(line, tempCell);
    }
    findStartAndTarget();
    this->current = this->start;
}

// Public Methods

bool Maze::printMaze(){
    Cell* tempCellPtr;
    Cell* tempLeftCellPtr;
    tempCellPtr = this->zeroCell;
    tempLeftCellPtr = this->zeroCell;
    int i = 0;
    while(tempCellPtr->down != nullptr){
        while (tempCellPtr->right != nullptr) {
            cout << tempCellPtr->value;
            tempCellPtr = tempCellPtr->right;
        }
        cout << tempCellPtr->value << endl; // Accounts for last element
        tempCellPtr = tempLeftCellPtr->down;
        tempLeftCellPtr = tempLeftCellPtr->down;
        i++;
    }

    while (tempCellPtr->right != nullptr) { // Accounts for last row
            cout << tempCellPtr->value;
            tempCellPtr = tempCellPtr->right;
    }
    cout << tempCellPtr->value << endl;
    return true;
}


bool Maze::solveMaze(const int maxSteps = 1000) { // Max num of steps to avoid infinite loops
    if (this->start == nullptr){
        cout << "Warning: Could not solve maze due to no start point being found" << endl;
        return false;
    }
    else if (this->target == nullptr){
        cout << "Warning: Could not solve maze due to no target point being found" << endl;
        return false;
    }
    else {
        int stepCount = 0;
        unsigned short direction = 0; // 0:right, 1:down, 2:left, 3:up
        while (this->current != this->target && stepCount < maxSteps) {
            
            if (this->previous == nullptr){
                if (!findNextNode(0)) {
                    cout << "There is no solution" << endl;
                    return false;
                }
            }
            else if (this->previous == this->current->right){
                if (!findNextNode(1)) {
                    cout << "There is no solution" << endl;
                    return false;
                }
            }
            else if (this->previous == this->current->down){
                if (!findNextNode(2)) {
                    cout << "There is no solution" << endl;
                    return false;
                }
            }
            else if (this->previous == this->current->left){
                if (!findNextNode(3)) {
                    cout << "There is no solution" << endl;
                    return false;
                }
            }
            else if (this->previous == this->current->up){
                if (!findNextNode(0)) {
                    cout << "There is no solution" << endl;
                    return false;
                }
            }
            stepCount++;
        }
        if (this->current == this->target){
            this->start->value = ' ';
            return true;
        }
        else if (stepCount >= maxSteps) {
            cout << "Maximum number of steps reached: There is either no solution or the solution is too complex to be calculated in " << 
            maxSteps << " steps." << endl;
            return false;
        }
        else {
            cout << "Programming error in solve maze.  This should not happen." << endl;
            return false;
        }
    }
}

// Private methods

bool Maze::findNextNode(short direction){
    for (short i = 0; i < 4; i++){
        if (direction == 0) {
            if (moveRight()){
                return true;
            } 
            else direction = 1;
        }
        else if (direction == 1) {
            if (moveDown()){
                return true;
            } 
            else direction = 2;
        }
        else if (direction == 2){
            if (moveLeft()){
                return true;
            } 
            else direction = 3;
        }
        else if (direction == 3){
            if (moveUp()){
                return true;
            } 
            else direction = 0;
        }
        else {
            cout << "Programming error in solve maze.  This should not happen." << endl;
            return false;
        }
    }
    return false;
}

Cell* Maze::insertCellRow(string newRowString, Cell* prevRowFirstCell = nullptr){
    Cell* newCell = nullptr;
    Cell* prevCell = nullptr;
    Cell* prevRowCell = prevRowFirstCell;
    Cell* leftmostCell;
    for (int i = 0; i < newRowString.length(); i++) {
        newCell = new Cell;
        if (newCell == nullptr) break; // Accounts for running out of memory
        if (i == 0) leftmostCell = newCell;
        // Assign available new cell pointers
        newCell->value = newRowString[i];
        newCell->left = prevCell;
        if (prevRowCell != nullptr) newCell->up = prevRowCell;

        // Assign available previous cell pointers
        if (prevCell != nullptr) prevCell->right = newCell;

        // Assign available pointers from the cenn above the new cell
        if (prevRowCell != nullptr) prevRowCell->down = newCell;

        else {  // Assigning zero cell value in best performance spot without over complicating code
            if (prevCell == nullptr) this->zeroCell = newCell;
        }
        
        prevCell = newCell;
        if (prevRowFirstCell != nullptr) prevRowCell = prevRowCell->right;
    }
    if (leftmostCell == nullptr){
        return nullptr;
    }
    return leftmostCell;
}

bool Maze::findStartAndTarget(){
    Cell* tempCell = this->zeroCell;
    bool startFound = false;
    bool targetFound = false;

    while (tempCell->right != nullptr){
        if (tempCell->value == '0'){
            if (targetFound && startFound){
                cout << "Warning: There are more that two candidate start/target cells found." << endl;
                return true;
            }
            else if (startFound){
                this->target = tempCell;
                targetFound = true;
            }
            else {
                this->start = tempCell;
                startFound = true;
            }
        }
        tempCell = tempCell->right;
    }
    while (tempCell->down != nullptr){
        if (tempCell->value == '0'){
            if (targetFound && startFound){
                cout << "Warning: There are more that two candidate start/target cells found." << endl;
                return true;
            }
            else if (startFound){
                this->target = tempCell;
                targetFound = true;
            }
            else {
                this->start = tempCell;
                startFound = true;
            }
        }
        tempCell = tempCell->down;
    }
    while (tempCell->left != nullptr){
        if (tempCell->value == '0'){
            if (targetFound && startFound){
                cout << "Warning: There are more that two candidate start/target cells found." << endl;
                return true;
            }
            else if (startFound){
                this->target = tempCell;
                targetFound = true;
            }
            else {
                this->start = tempCell;
                startFound = true;
            }
        }
        tempCell = tempCell->left;
    }
    while (tempCell->up != this->zeroCell){
        if (tempCell->value == '0'){
            if (targetFound && startFound){
                cout << "Warning: There are more that two candidate start/target cells found." << endl;
                return true;
            }
            else if (startFound){
                this->target = tempCell;
                targetFound = true;
            }
            else {
                this->start = tempCell;
                startFound = true;
            }
        }
        tempCell = tempCell->up;
    }
    if (startFound && targetFound) return true;
    else {
        cout << "Warning: The start and/or target cell was not found." << endl;
        return false;
    }
}

bool Maze::moveRight() {
    // Only looking for values if 0 prevents infinite loops
    if (this->current->right != nullptr && (this->current->right->value == '0' || this->current->right->value == ' ')) {
        if (this->current->right->value == ' ') this->current->value = '0';
        this->previous = this->current;
        this->current = this->current->right;
        this->current->value = ' ';
        return true;
    }
    else {
        return false;
    }
}

bool Maze::moveLeft(){
    if (this->current->left != nullptr && (this->current->left->value == '0' || this->current->left->value == ' ')) {
        if (this->current->left->value == ' ') this->current->value = '0';
        this->previous = this->current;
        this->current = this->current->left;
        this->current->value = ' ';
        return true;
    }
    else return false;
}

bool Maze::moveUp(){
    if (this->current->up != nullptr && (this->current->up->value == '0' || this->current->up->value == ' ')) {
        if (this->current->up->value == ' ') this->current->value = '0';
        this->previous = this->current;
        this->current = this->current->up;
        this->current->value = ' ';
        return true;
    }
    else return false;
}

bool Maze::moveDown(){
    if (this->current->down != nullptr && (this->current->down->value == '0' || this->current->down->value == ' ')) {
        if (this->current->down->value == ' ') this->current->value = '0';
        
        this->previous = this->current;
        this->current = this->current->down;
        this->current->value = ' ';
        return true;
    }
    else return false;
}