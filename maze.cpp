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
}

// Methods

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
        newCell->up = prevRowCell;

        // Assign available previous cell pointers
        prevCell->right = newCell;

        // Assign available pointers from the cenn above the new cell
        if (prevRowCell != nullptr) prevRowCell->down = newCell;
        else {  // Assigning zero cell value in best performance spot without over complicating code
            if (prevCell == nullptr) this->zeroCell = newCell;
        }

        prevCell = newCell;
        prevRowCell = prevRowCell->right;
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
                cout << "Error: There were more that two candidate start/target cells found." << endl;
                return false;
            }
            else if (startFound){
                this->target = tempCell;
                targetFound = true;
            }
            else {
                this->start = tempCell;
                startFound = true;
            }
            tempCell = tempCell->right;
        }
    }
    while (tempCell->down != nullptr){
        if (tempCell->value == '0'){
            if (targetFound && startFound){
                cout << "Error: There were more that two candidate start/target cells found." << endl;
                return false;
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
                cout << "Error: There were more that two candidate start/target cells found." << endl;
                return false;
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
                cout << "Error: There were more that two candidate start/target cells found." << endl;
                return false;
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
    return false;
}

bool Maze::printMaze(){
    Cell* tempCellPtr;
    while(tempCellPtr->down != nullptr){
        string line;
        tempCellPtr = this->zeroCell;
        while (tempCellPtr->right != nullptr) {
            line.push_back(tempCellPtr->value);
            tempCellPtr = tempCellPtr->right;
        }
        cout << line << endl;
    }
    return true;
}