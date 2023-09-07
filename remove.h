#ifndef __REMOVE_H__
#define __REMOVE_H__
#include "grid.h"

typedef struct {
    int row;
    int col;
    int wall_removed;
    int steps;
} Node;

int shortestPathWithWall(Graph* graph, GraphNode* start);
void minTimeWithRemoval(Graph* graph, GraphNode* startNode);

#endif
