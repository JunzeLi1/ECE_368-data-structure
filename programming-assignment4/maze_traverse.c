#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grid.h"
#include "maze_traverse.h"

Graph* createGraph(int rows, int cols) {
    Graph* graph = malloc(sizeof(Graph));
    graph->rows = rows;
    graph->cols = cols;
    graph->nodes = malloc(rows * sizeof(GraphNode*));
    for (int i = 0; i < rows; i++) {
        graph->nodes[i] = malloc(cols * sizeof(GraphNode));
        for (int j = 0; j < cols; j++) {
            GraphNode node = {i, j, INT_MAX, INT_MAX, INT_MAX, INT_MAX, -1, 0, NULL};
            graph->nodes[i][j] = node;
        }
    }
    return graph;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->rows; i++) {
        free(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);
}

void bfs(Graph* graph, GraphNode* startNode) {
    startNode->dist = 0;
    GraphNode* queue = malloc(graph->rows * graph->cols * sizeof(GraphNode));
    int front = 0;
    int back = 0;
    queue[back++] = *startNode;
    while (front < back) {
        GraphNode node = queue[front++];
        // Check all four directions
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int newRow = node.row + directions[i][0];
            int newCol = node.col + directions[i][1];
            if (newRow >= 0 && newRow < graph->rows && newCol >= 0 && newCol < graph->cols) {
                GraphNode* neighbor = &graph->nodes[newRow][newCol];
                if (neighbor->isWall == 0 && neighbor->dist == -1) {
                    neighbor->dist = node.dist + 1;
                    neighbor->prev = &graph->nodes[node.row][node.col];  // store the address from the graph
                    queue[back++] = *neighbor;
                }
            }
        }
    }
    free(queue);
}

/*
void printPath(GraphNode* node) {
    if (node->dist == -1) {
        printf("-1\n");
        return;
    }

    GraphNode** path = malloc(node->dist * sizeof(GraphNode*));
    GraphNode* current = node;
    for (int i = node->dist - 1; i >= 0; i--) {
        path[i] = current;
        current = current->prev;
    }

    printf("(");
    for (int i = 0; i < node->dist; i++) {
        printf("%d,%d", path[i]->row, path[i]->col);
        if (i != node->dist - 1) {
            printf("),(");
        }
    }
    printf(")\n");
    free(path);
}*/

void printPath(GraphNode* node) {
    if (node->dist == -1) {
        printf("-1\n");
        return;
    }

    // Count nodes
    int count = 0;
    GraphNode* current = node;
    while (current != NULL) {
        count++;
        current = current->prev;
    }

    // Save path
    GraphNode** path = malloc(count * sizeof(GraphNode*));
    current = node;
    for (int i = count - 1; i >= 0; i--) {
        path[i] = current;
        current = current->prev;
    }

    // Print path
    for (int i = 0; i < count; i++) {
        printf("(%d,%d)", path[i]->row, path[i]->col);
        if (i < count - 1) {
            printf(",");
        }
    }
    printf("\n");

    free(path);
}



/*
void resetGraph(Graph* graph) {
    for (int i = 0; i < graph->rows; i++) {
        for (int j = 0; j < graph->cols; j++) {
            graph->nodes[i][j].dist = -1;
            graph->nodes[i][j].prev = NULL;
        }
    }
}

void bfsOptimized(Graph* graph, GraphNode* startNode, int** distances) {
    startNode->dist = 0;
    GraphNode* queue = malloc(graph->rows * graph->cols * sizeof(GraphNode));
    int front = 0;
    int back = 0;
    queue[back++] = *startNode;
    while (front < back) {
        GraphNode node = queue[front++];
        // Check all four directions
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int newRow = node.row + directions[i][0];
            int newCol = node.col + directions[i][1];
            if (newRow >= 0 && newRow < graph->rows && newCol >= 0 && newCol < graph->cols) {
                GraphNode* neighbor = &graph->nodes[newRow][newCol];
                if (!neighbor->isWall && distances[newRow][newCol] == -1) {
                    distances[newRow][newCol] = distances[node.row][node.col] + 1;
                    queue[back++] = *neighbor;
                }
            }
        }
    }
    free(queue);
}

void processRemoveModeOptimized(Graph* graph, GraphNode* startNode) {
    int** distances1 = create2DArray(graph->rows, graph->cols, -1);
    int** distances2 = create2DArray(graph->rows, graph->cols, -1);

    bfsOptimized(graph, startNode, distances1);
    bfsOptimized(graph, &graph->nodes[0][0], distances2);

    int minTime = -1;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < graph->rows; i++) {
        for (int j = 0; j < graph->cols; j++) {
            if (graph->nodes[i][j].isWall) {
                // Calculate the minimum time if this wall is removed
                int minTime1 = INT_MAX;
                int minTime2 = INT_MAX;
                for (int k = 0; k < 4; k++) {
                    int newRow = i + directions[k][0];
                    int newCol = j + directions[k][1];
                    if (newRow >= 0 && newRow < graph->rows && newCol >= 0 && newCol < graph->cols) {
                        if (!graph->nodes[newRow][newCol].isWall) {
                            minTime1 = min(minTime1, distances1[newRow][newCol]);
                            minTime2 = min(minTime2, distances2[newRow][newCol]);
                        }
                    }
                }
                if (minTime1 != INT_MAX && minTime2 != INT_MAX && (minTime == -1 || minTime1 + minTime2 + 2 < minTime)) {
                    minTime = minTime1 + minTime2 + 2;
                }
            }
        }
    }

    printf("%d\n", minTime);

    delete2DArray(distances1, graph->rows);
    delete2DArray(distances2, graph->rows);
}

void delete2DArray(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

int** create2DArray(int rows, int cols, int initValue) {
    int** array = (int**) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        array[i] = (int*) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            array[i][j] = initValue;
        }
    }
    return array;
}
*/

/*
void bfsRemove(Graph* graph, GraphNode* startNode, GraphNode* removedNode) {
    removedNode->isWall = 0;  // temporarily remove the wall
    startNode->dist = 0;
    GraphNode* queue = malloc(graph->rows * graph->cols * sizeof(GraphNode));
    int front = 0;
    int back = 0;
    queue[back++] = *startNode;
    while (front < back) {
        GraphNode node = queue[front++];
        // Check all four directions
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int newRow = node.row + directions[i][0];
            int newCol = node.col + directions[i][1];
            if (newRow >= 0 && newRow < graph->rows && newCol >= 0 && newCol < graph->cols) {
                GraphNode* neighbor = &graph->nodes[newRow][newCol];
                if (neighbor->isWall == 0 && neighbor->dist == -1) {
                    neighbor->dist = node.dist + 1;
                    neighbor->prev = &graph->nodes[node.row][node.col];
                    queue[back++] = *neighbor;
                }
            }
        }
    }
    free(queue);
    removedNode->isWall = 1;  // restore the wall
}


void processRemoveMode(Graph* graph, GraphNode* startNode) {
    int minTime = -1;
    for (int i = 0; i < graph->rows; i++) {
        for (int j = 0; j < graph->cols; j++) {
            if (graph->nodes[i][j].isWall) {
                resetGraph(graph);
                bfsRemove(graph, startNode, &graph->nodes[i][j]);
                if (graph->nodes[0][0].dist != -1 && (minTime == -1 || graph->nodes[0][0].dist < minTime)) {
                    minTime = graph->nodes[0][0].dist;
                }
            }
        }
    }
    printf("%d\n", minTime);
}*/




/*
int main(int argc, char* argv[]) {
    if (argc != 3 || argv[1][0] != '-') {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    char* fname = argv[2];
    FILE* file = fopen(fname, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
    }

    int rows, cols, startRow, startCol;
    fscanf(file, "(%d,%d)\n", &rows, &cols);
    fscanf(file, "(%d,%d)\n", &startRow, &startCol);

    // Create the graph
    Graph* graph = createGraph(rows, cols);

    // Load grid data and validate it
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = fgetc(file);
            if (c == '1') {
                graph->nodes[i][j].isWall = 1;
            } else if (c != '0') {
                fprintf(stderr, "Invalid grid data\n");
                return EXIT_FAILURE;
            }
        }
        fgetc(file);  // Skip newline
    }
    fclose(file);

    // Validate start node
    if (graph->nodes[startRow][startCol].isWall) {
        fprintf(stderr, "Start location is a wall\n");
        return EXIT_FAILURE;
    }

    // Decide on the mode and process accordingly
    if (argv[1][1] == 't') {
        bfs(graph, &graph->nodes[startRow][startCol]);
        printf("%d,%d,%d,%d\n",
                graph->nodes[0][0].dist,
                graph->nodes[0][cols-1].dist,
                graph->nodes[rows-1][cols-1].dist,
                graph->nodes[rows-1][0].dist);
    } else if (argv[1][1] == 'p') {
        bfs(graph, &graph->nodes[startRow][startCol]);
        printPath(&graph->nodes[0][0]);
        printPath(&graph->nodes[0][cols-1]);
        printPath(&graph->nodes[rows-1][cols-1]);
        printPath(&graph->nodes[rows-1][0]);
    } else if (argv[1][1] == 'r') {
        processRemoveMode(graph, &graph->nodes[startRow][startCol]);
    } else {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    // Clean up
    freeGraph(graph);
    return EXIT_SUCCESS;
}
*/
