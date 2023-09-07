#ifndef __GRID_H__
#define __GRID_H__

typedef struct _GraphNode {
    int row;
    int col;
    int weightUp;
    int weightDown;
    int weightLeft ;
    int weightRight ;
    int dist;
    int isWall;
    struct _GraphNode* prev;
} GraphNode;

typedef struct _Graph {
    int rows;
    int cols;
    GraphNode** nodes;
} Graph;

#define min(a,b) ((a) < (b) ? (a) : (b))

#endif
