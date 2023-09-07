#ifndef __MAZE_TRAVERSE_H__
#define __MAZE_TRAVERSE_H__
#include "grid.h"

Graph* createGraph(int rows, int cols);
void freeGraph(Graph* graph);
void bfs(Graph* graph, GraphNode* startNode);
void printPath(GraphNode* node);
void resetGraph(Graph* graph);
//void bfsRemove(Graph* graph, GraphNode* startNode, GraphNode* removedNode);
//void processRemoveMode(Graph* graph, GraphNode* startNode);
#endif
