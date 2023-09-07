#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grid.h"
#include "maze_traverse.h"
#include "remove.h"

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
    //fscanf(file, "(%d,%d)\n", &rows, &cols);
    //fscanf(file, "(%d,%d)\n", &startRow, &startCol);

    if(fscanf(file, "(%d,%d)\n", &rows, &cols) != 2) {
    fprintf(stderr, "Failed to read rows and cols\n");
    return EXIT_FAILURE;
    }
    if(fscanf(file, "(%d,%d)\n", &startRow, &startCol) != 2) {
    fprintf(stderr, "Failed to read startRow and startCol\n");
    return EXIT_FAILURE;
    }

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
        minTimeWithRemoval(graph, &graph->nodes[startRow][startCol]);
    } 
    else {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    // Clean up
    freeGraph(graph);
    return EXIT_SUCCESS;
}
