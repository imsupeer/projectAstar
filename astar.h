#ifndef ASTAR_H
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 6
#define COLS 6

typedef struct Node {
    int row;
    int col;
    struct Node* parent;
    double g_cost;
    double h_cost;
    double f_cost;
    struct Node* next;
} Node;

double heuristic(int start_row, int start_col, int end_row, int end_col);
int isValid(int row, int col);
int isUnBlocked(int grid[][COLS], int row, int col);
int isDestination(int row, int col, Node* dest);
void tracePath(Node* dest);
void AStarSearch(int grid[][COLS], Node* start, Node* dest);
Node* createNode(int row, int col);
void printGrid(int grid[][COLS]);

#endif
