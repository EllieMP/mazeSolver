#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Cell {
    int value; // 1 for wall 0 for 
    Cell* left;
    Cell* right;
    Cell* up;
    Cell* down;
};

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
        Cell* start;
        Cell* target;
        Cell* current;
        Cell* previous;
};