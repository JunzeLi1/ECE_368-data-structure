#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "grid.h"
#include "maze_traverse.h"
#include "remove.h"

/*
int shortestPathWithWall(Graph* graph, int startRow, int startCol, int destRow, int destCol) {
    int rows = graph->rows;
    int cols = graph->cols;
    int ***visited = (int***)malloc(rows * sizeof(int**));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int**)malloc(cols * sizeof(int*));
        for (int j = 0; j < cols; j++) {
            visited[i][j] = (int*)malloc(2 * sizeof(int));
            visited[i][j][0] = -1;
            visited[i][j][1] = -1;
        }
    }

    Node *queue = (Node*)malloc(rows * cols * 2 * sizeof(Node));
    int front = 0;
    int rear = 0;

    Node start_node = {startRow, startCol, 0, 0};
    queue[rear++] = start_node;
    visited[startRow][startCol][0] = 0;

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    while (front < rear) {
        Node current = queue[front++];
        
        if (current.row == destRow && current.col == destCol) {
            return current.steps;
        }

        for (int i = 0; i < 4; i++) {
            int next_row = current.row + dr[i];
            int next_col = current.col + dc[i];

            if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols) {
                if (graph->nodes[next_row][next_col].isWall == 0 &&
                    visited[next_row][next_col][current.wall_removed] == -1) {
                    Node next_node = { next_row, next_col, current.wall_removed, current.steps + 1 };
                    queue[rear++] = next_node;
                    visited[next_row][next_col][current.wall_removed] = current.steps + 1;
                } else if (graph->nodes[next_row][next_col].isWall == 1 && !current.wall_removed &&
                           visited[next_row][next_col][1] == -1) {
                    Node next_node = { next_row, next_col, 1, current.steps + 1 };
                    queue[rear++] = next_node;
                    visited[next_row][next_col][1] = current.steps + 1;
                }
            }
        }
    }
    return -1;
}

void minTimeWithRemoval(Graph* graph, GraphNode* startNode) {
    int shortestSteps = shortestPathWithWall(graph, startNode->row, startNode->col, 0, 0);
    if (shortestSteps != -1) {
        printf("%d\n", shortestSteps);
    } else {
        printf("%d\n", -1);
    }
}*/

int shortestPathWithWall(Graph* graph, GraphNode* start) {
    int rows = graph->rows;
    int cols = graph->cols;
    // initialize visited boolean 3D array
    bool ***visited = (bool***)malloc(rows * sizeof(bool**));
    for (int i = 0; i < rows; i++) {
        visited[i] = (bool**)malloc(cols * sizeof(bool*));
        for (int j = 0; j < cols; j++) {
            visited[i][j] = (bool*)malloc(2 * sizeof(bool));
            visited[i][j][0] = false;
            visited[i][j][1] = false;
        }
    }

    // initialize queue of nodes
    Node *queue = (Node*)malloc(rows * cols * 2 * sizeof(Node));
    int front = 0;
    int rear = 0;

    Node start_node = {start->row, start->col, false, 0};
    queue[rear++] = start_node;
    visited[start->row][start->col][0] = true;

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    while (front < rear) {
        Node current = queue[front++];
        
        if (current.row == 0 && current.col == 0) {
            // Free memory and return
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    free(visited[i][j]);
                }
                free(visited[i]);
            }
            free(visited);
            free(queue);
            return current.steps;
        }

        // Traverse neighbors
        for (int i = 0; i < 4; i++) {
            int next_row = current.row + dr[i];
            int next_col = current.col + dc[i];

            if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols) {
                if (!graph->nodes[next_row][next_col].isWall && !visited[next_row][next_col][current.wall_removed]) {
                    Node next_node = { next_row, next_col, current.wall_removed, current.steps + 1 };
                    queue[rear++] = next_node;
                    visited[next_row][next_col][current.wall_removed] = true;
                } else if (graph->nodes[next_row][next_col].isWall && !current.wall_removed && !visited[next_row][next_col][true]) {
                    Node next_node = { next_row, next_col, true, current.steps + 1 };
                    queue[rear++] = next_node;
                    visited[next_row][next_col][true] = true;
                }
            }
        }
    }

    // Free memory and return -1 as no path was found
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(visited[i][j]);
        }
        free(visited[i]);
    }
    free(visited);
    free(queue);
    return -1;
}

void minTimeWithRemoval(Graph* graph, GraphNode* startNode) {
    int shortestSteps = shortestPathWithWall(graph, startNode);
    if (shortestSteps != -1) {
        printf("%d\n", shortestSteps);
    } else {
        printf("%d\n", -1);
    }
}

