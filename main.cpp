#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"
using namespace std;

// Global configuration values

const int MAX_SOLVE_MAZE_MOVES = 10000; // Sets maximum amount of moves solving a maze will allow.

int main( ) {
    string fileName = "";
    cin >> fileName; // Gets file name from user

    fstream fileStream;
    fileStream.open(fileName);
    if(fileStream.fail()){ // Checks if file was opened properly
        cout << "Error: There was an issue opening the file.";
    }
    else {
        Maze mazeToSolve(fileStream); // Declare maze from file stream
        if (mazeToSolve.solveMaze(MAX_SOLVE_MAZE_MOVES)){
            mazeToSolve.printMaze();
        }
    }
}