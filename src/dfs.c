#include "dfs.h"
#include "maze_parse.h"

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
      Vertex* nup = NULL;
      nup->x = current->x;
      nup->y = current->y - 1;

      Vertex* ndown = NULL;
      ndown->x = current->x;
      ndown->y = current->y + 1;

      Vertex* nleft = NULL;
      nleft->x = current->x - 1;
      nleft->y = current->y;

      Vertex* nright = NULL;
      nright->x = current->x + 1;
      nleft->y = current->y;
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
