#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"
using namespace std;

// Functiopn prototypes
int printGraph(Maze);


int main( ) {
    string fileName = "";
    cin >> fileName; // Gets file name from user

    fstream fileStream;
    fileStream.open(fileName);
    if(fileStream.fail()){
        cout << "There was an issue opening the file";
    }
    else {
        Maze mazeToSolve(fileStream); // Declare maze
    }
}

// Prints the graph row by row
int printGraph(vector<vector<int>> graphToPrint){
    for(vector<int> i: graphToPrint){
        for(int j: i) cout << j;
        cout << endl;
    }
    return 0;
}