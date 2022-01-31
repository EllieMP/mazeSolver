#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Maze{
    public:
    // Constructors
        Maze(fstream&); // Uses an input file stream by refrence to map the maze

    // Methods
        vector<int> getCurrentLocation(); // Returns a vector with the current down and right distance from the top left cell
        bool moveRight();
        bool moveLeft();
        bool moveUp();
        bool moveDown();

    private:
        vector<vector<int>> graph;
        int start [2];
        int target [2];
        int current [2];
        int previous [2];
};