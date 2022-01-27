#include <cstddef> // needed for NULL on newer compilers
#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"

// Constructors

Maze::Maze(fstream& fstream){string line;
    // Parse filestream into 2d vector of 1s and 0s
    while(!fstream.eof()) {// Loop until file ends
        getline(fstream, line); // Get line from file and wipe previous line
        vector<int> tempVector; // Populate vector with appropriate 1s and 0s
        for (int i = 0; i < line.length(); i++){ 
            tempVector.push_back(line[i] - '0'); // Assumes charecter integer values follow ascii standards
        }
        this->graph.push_back(tempVector); // Append current line to graph as a vector of 1s and 0s
    }

    // Find start and target cell
    for(int i = 0; i < graph.at(0).size(); i++){
        
    }
        // Search top row for a zero
        // Search all middle rows for a zero
        // Search bottom row for a zero
    // If there are more than two zeros, print a
}