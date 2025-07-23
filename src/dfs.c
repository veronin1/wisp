#include "dfs.h"
#include "maze_parse.h"

int dfs(Maze* maze) {
  VertexStack stack;
  stack.top = 0;
  stack.data[stack.top++] = maze->start;

  while (stack.top != 0) {
    for (size_t i = 0; i < 4; ++i) {
    }
  }
  return 0;
}

Vertex* pop(VertexStack* stack) {
  if (!stack || stack->top) {
    return NULL;
  }
  Vertex* top = stack->data[stack->top - 1];
  stack->data[stack->top - 1] = 0;
  stack->top--;
  return top;
}
