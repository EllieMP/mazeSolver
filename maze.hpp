#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Cell{
    char value; // One less step when handeling the input and output streams
    Cell* up;
    Cell* down;
    Cell* left;
    Cell* right;
};

/*
    The maze class represents a maze as a dynamic 2d linked list of Cell structures
*/
class Maze{
    public:
    // Constructors and Destructors
        Maze(); // Create an empty maze
        Maze(fstream&); // Creates a maze based on an open filestream

    // Inserting Cells

    // Public Methods
        bool printMaze(); // Prints the maze row by row in std:cout
        bool solveMaze(const int);

    private:

    // Private Methods
        bool findStartAndTarget(); // Finds start and target cells
        Cell* insertCellRow(string, Cell*);
        bool findNextNode(short);
        bool moveRight();
        bool moveLeft();
        bool moveUp();
        bool moveDown();

    // Private values
        Cell* start;
        Cell* target;
        Cell* current;
        Cell* previous;
        // A convienent cell pointer that points to the top left cell trading 4 to 8 byte of memory for performance on most machines
        Cell* zeroCell;
};