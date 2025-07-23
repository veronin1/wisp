#ifndef DFS_H
#define DFS_H

#include "maze_parse.h"

typedef struct {
  Vertex *data[MAX_WIDTH * MAX_HEIGHT];
  size_t top;
} VertexStack;

int dfs(Maze *maze);
void retrace_path(Vertex *end, Maze *maze);
Vertex *pop(VertexStack *stack);
void push(VertexStack *stack, Vertex *value);

#endif
