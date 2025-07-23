#include "dfs.h"
#include <stdlib.h>
#include "maze_parse.h"

int directionX[4] = {0, 0, -1, 1};
int directionY[4] = {-1, 1, 0, 0};

int dfs(Maze* maze) {
  VertexStack stack;
  stack.top = 0;
  stack.data[stack.top++] = maze->start;

  while (stack.top != 0) {
    Vertex* current = pop(&stack);
    if (!current) {
      continue;
    }
    if (current == maze->end) {
      break;
    }
    if (!current->visited) {
      current->visited = 1;
    }
    for (size_t i = 0; i < 4; ++i) {
    }
  }
  return 0;
}

Vertex* pop(VertexStack* stack) {
  if (!stack || stack->top == 0) {
    return NULL;
  }
  Vertex* top = stack->data[stack->top - 1];
  stack->data[stack->top - 1] = NULL;
  stack->top--;
  return top;
}
