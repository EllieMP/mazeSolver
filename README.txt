A class and use case that takes a txt file representing a 2d maze where 1s and 0s where 1s represent walls and 0s represent
the path one can walk on that outputs a maze with ' ' representing the path one would walk from the start to the end of the maze.
1s on the border of the maze represent the edges of the maze while 0s on the edges of the maze represent entrance/exit points.

Precondition: There are at least two entrance/exit points on the border of the maze.
Precondition: The size of each row of the maze is the same.

Usage: ./a.out inputFilePath

* Note: For very large mazes, the MAX_SOLVE_MAZE_MOVES variable in main.cpp should be increased.
* Note: This does not find the most efficent way through the maze.
* Note: This program runs syncrynously and stops after finding a solution as to not waste resources

Sample Input:
111111111111111
100000001000001
101110101010111
000010101010001
111110111011101
100000000010001
101010111010111
101010001010001
101011101011101
101000101010101
101110111010101
100010001000100
111111111111111

Sample Output:
111111111111111
1     001   001
1 111 101 1 111
  001 101 1   1
11111 111 111 1
10000     1   1
10101011101 111
10101000101   1
1010111010111 1
1010001010101 1
1011101110101 1
1000100010001  
111111111111111
