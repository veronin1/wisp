#ifndef DFS_H
#define DFS_H

#include "maze.h"

#define DFS_SUCCESS 0
#define DFS_FAILURE -1

typedef struct {
  Vertex *data[MAX_WIDTH * MAX_HEIGHT];
  size_t top;
} VertexStack;

int dfs(Maze *maze);
Vertex *pop(VertexStack *stack);
int push(VertexStack *stack, Vertex *value);

#endif // DFS.H
