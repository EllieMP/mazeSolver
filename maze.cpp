#include <cstddef> // needed for NULL on newer compilers
#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"

// Constructors

Maze::Maze(fstream& fstream){
    string line;
    // Parse filestream into 2d vector of 1s and 0s
    while(!fstream.eof()) { // Loop until file ends
        getline(fstream, line); // Get line from file and wipe previous line
        vector<int> tempVector; // Populate vector with appropriate 1s and 0s
        for (int i = 0; i < line.length(); i++) { 
            tempVector.push_back(line[i] - '0'); // Assumes charecter integer values follow ascii standards
        }
        this->graph.push_back(tempVector); // Append current line to graph as a vector of 1s and 0s
    }

    // Find start and target cell
    bool startFound = false;
    bool targetFound = false;
    // Check top & bottom rows
    for(int i = 0; i < this->graph.at(0).size(); i++) {
        if(graph.front().at(i) == 0){
            if (startFound && targetFound){
                cout << "Error: More than two possable start and target locations found.";
                break;
            }
            else if (startFound) {
                this->target[0] = i;
                this->target[1] = 0;
                targetFound = true;
            }
            else {
                this->start[0] = i;
                this->start[1] = 0;
                startFound = true;
            }
        }
        if (graph.back().at(i) == 0){
            if (startFound && targetFound){
                cout << "Error: More than two possable start and target locations found.";
                break;
            }
            else if (startFound) {
                this->target[0] = i;
                this->target[1] = graph.size() - 1;
                targetFound = true;
            }
            else {
                this->start[0] = i;
                this->start[1] = graph.size() - 1;
                startFound = true;
            }
        }
    }

    // Check left and right collumns for 0s
        // Note: This is put second because it's less efficent and not always necessary
    for(int i = 1; i < this->graph.size(); i++){ // Start at second row and end at second to last row to avoid redundency
        if (graph.at(i).front() == 0){ // Check left most value in a row
            if (startFound && targetFound){
                cout << "Error: More than two possable start and target locations found.";
                break;
            }
            else if (startFound) {
                this->target[0] = 0;
                this->target[1] = i;
                targetFound = true;
            }
            else {
                this->start[0] = 0;
                this->start[1] = i;
                startFound = true;
            }
        }
        if (graph.at(i).back() == 0){ // Check right most value in a row
            if (startFound && targetFound){
                cout << "Error: More than two possable start and target locations found.";
                break;
            }
            else if (startFound) {
                this->target[0] = this->graph.at(i).size() - 1;
                this->target[1] = i;
                targetFound = true;
            }
            else {
                this->start[0] = this->graph.at(i).size() - 1;
                this->start[1] = i;
                startFound = true;
            }
        }
    }
    //cout << this->start[0] << "\t" << this->start[1] << endl;
    //cout << this->target[0] << "\t" << this->target[1];
}