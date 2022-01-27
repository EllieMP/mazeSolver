#include <iostream>
#include <string>
#include <fstream>
#include "maze.hpp"
using namespace std;

// Functiopn prototypes


int main( ) {
    string fileName = "";
    cin >> fileName; // Gets file name from user

    fstream fileStream;
    fileStream.open(fileName);
    if(fileStream.fail()){
        cout << "There was an issue opening the file";
    }
    else {
        Maze a(fileStream);
    }
}