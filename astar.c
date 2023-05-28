#include "astar.h"

double heuristic(int start_row, int start_col, int end_row, int end_col) {
    return abs(start_row - end_row) + abs(start_col - end_col);
}

int isValid(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

int isUnBlocked(int grid[][COLS], int row, int col) {
    return grid[row][col] == 1;
}

int isDestination(int row, int col, Node* dest) {
    return (row == dest->row) && (col == dest->col);
}

void tracePath(Node* dest) {
    if (dest->parent != NULL) {
        tracePath(dest->parent);
        printf("-> (%d,%d) ", dest->row, dest->col);
    } else {
        printf("(%d,%d) ", dest->row, dest->col);
    }
}

void AStarSearch(int grid[][COLS], Node* start, Node* dest) {
    if (!isValid(start->row, start->col) || !isValid(dest->row, dest->col)) {
        printf("Posicao inicial ou destino esta fora dos limites do grid.\n");
        return;
    }

    if (!isUnBlocked(grid, start->row, start->col) || !isUnBlocked(grid, dest->row, dest->col)) {
        printf("Posicao inicial ou destino eh uma celula bloqueada.\n");
        return;
    }

    if (isDestination(start->row, start->col, dest)) {
        printf("Voce ja esta no destino.\n");
        return;
    }

    int closedList[ROWS][COLS] = {0};

    Node* openList = createNode(start->row, start->col);
    openList->g_cost = 0.0;
    openList->h_cost = heuristic(start->row, start->col, dest->row, dest->col);
    openList->f_cost = openList->g_cost + openList->h_cost;

    while (openList != NULL) {
        Node* currentNode = openList;
        openList = openList->next;

        int row = currentNode->row;
        int col = currentNode->col;

        closedList[row][col] = 1;

        double gNew, hNew, fNew;

        if (isValid(row - 1, col)) {
            if (isDestination(row - 1, col, dest)) {
                dest->parent = currentNode;
                printf("Caminho encontrado: ");
                tracePath(dest);
                return;
            } else if (!closedList[row - 1][col] && isUnBlocked(grid, row - 1, col)) {
                gNew = currentNode->g_cost + 1.0;
                hNew = heuristic(row - 1, col, dest->row, dest->col);
                fNew = gNew + hNew;

                Node* newNode = createNode(row - 1, col);
                newNode->parent = currentNode;
                newNode->g_cost = gNew;
                newNode->h_cost = hNew;
                newNode->f_cost = fNew;
                newNode->next = openList;

                openList = newNode;
            }
        }

        if (isValid(row + 1, col)) {
            if (isDestination(row + 1, col, dest)) {
                dest->parent = currentNode;
                printf("Caminho encontrado: ");
                tracePath(dest);
                return;
            } else if (!closedList[row + 1][col] && isUnBlocked(grid, row + 1, col)) {
                gNew = currentNode->g_cost + 1.0;
                hNew = heuristic(row + 1, col, dest->row, dest->col);
                fNew = gNew + hNew;

                Node* newNode = createNode(row + 1, col);
                newNode->parent = currentNode;
                newNode->g_cost = gNew;
                newNode->h_cost = hNew;
                newNode->f_cost = fNew;
                newNode->next = openList;

                openList = newNode;
            }
        }

        if (isValid(row, col - 1)) {
            if (isDestination(row, col - 1, dest)) {
                dest->parent = currentNode;
                printf("Caminho encontrado: ");
                tracePath(dest);
                return;
            } else if (!closedList[row][col - 1] && isUnBlocked(grid, row, col - 1)) {
                gNew = currentNode->g_cost + 1.0;
                hNew = heuristic(row, col - 1, dest->row, dest->col);
                fNew = gNew + hNew;

                Node* newNode = createNode(row, col - 1);
                newNode->parent = currentNode;
                newNode->g_cost = gNew;
                newNode->h_cost = hNew;
                newNode->f_cost = fNew;
                newNode->next = openList;

                openList = newNode;
            }
        }

        if (isValid(row, col + 1)) {
            if (isDestination(row, col + 1, dest)) {
                dest->parent = currentNode;
                printf("Caminho encontrado: ");
                tracePath(dest);
                return;
            } else if (!closedList[row][col + 1] && isUnBlocked(grid, row, col + 1)) {
                gNew = currentNode->g_cost + 1.0;
                hNew = heuristic(row, col + 1, dest->row, dest->col);
                fNew = gNew + hNew;

                Node* newNode = createNode(row, col + 1);
                newNode->parent = currentNode;
                newNode->g_cost = gNew;
                newNode->h_cost = hNew;
                newNode->f_cost = fNew;
                newNode->next = openList;

                openList = newNode;
            }
        }
    }

    printf("Nao foi possivel encontrar um caminho.\n");
}

Node* createNode(int row, int col) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->parent = NULL;
    newNode->g_cost = 0.0;
    newNode->h_cost = 0.0;
    newNode->f_cost = 0.0;
    newNode->next = NULL;
    return newNode;
}

void generateGrid(int grid[][COLS]) {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGrid(int grid[][COLS]) {
	int i, j;
    printf("Grid:\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printf("  ");
            } else {
                printf("##");
            }
        }
        printf("\n");
    }
    printf("\n");
}
