#include "dfs.h"
#include "globals.h"
#include "maze.h"

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

int dfs(Maze* maze) {
  VertexStack stack;
  stack.top = 0;
  stack.data[stack.top++] = maze->start;
  maze->start->visited = 1;

  while (stack.top != 0) {
    Vertex* current = pop(&stack);
    if (!current) {
      continue;
    }
    if (current == maze->end) {
      return DFS_SUCCESS;
    }
    for (size_t i = 0; i < 4; ++i) {
      int neighbourX = (int)current->x + directionX[i];
      int neighbourY = (int)current->y + directionY[i];

      if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
          neighbourY < (int)maze->height) {
        Vertex* neighbour = &maze->grid[neighbourY][neighbourX];

        if (!neighbour->is_wall && !neighbour->visited) {
          neighbour->visited = 1;
          neighbour->parent = current;
          push(&stack, neighbour);
        }
      }
    }
    ++totalSteps;
  }
  return DFS_FAILURE;
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

int push(VertexStack* stack, Vertex* value) {
  if (!stack) {
    return DFS_FAILURE;
  }

  if (value == NULL) {
    return DFS_FAILURE;
  }

  if (stack->top >= (size_t)MAX_WIDTH * MAX_HEIGHT) {
    return DFS_FAILURE;
  }

  stack->data[stack->top] = value;
  stack->top++;

  return DFS_SUCCESS;
}
