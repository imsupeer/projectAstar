#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "astar.h"

int main() {
    int grid[ROWS][COLS];

    generateGrid(grid);

    Node* start = createNode(0, 0);
    Node* dest = createNode(ROWS - 1, COLS - 1);

    printGrid(grid);
    AStarSearch(grid, start, dest);

    return 0;
}
