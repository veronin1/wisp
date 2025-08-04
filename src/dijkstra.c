#include "dijkstra.h"
#include "globals.h"
#include "maze.h"
#include "min_heap.h"

#include <limits.h>

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

typedef struct {
  int x;
  int y;
} Prev;

Prev prev[MAX_HEIGHT][MAX_WIDTH];
int dist[MAX_HEIGHT][MAX_WIDTH];

int dijkstra(Maze* maze) {
  MinHeap heap;
  heap.size = 0;

  // for each vertex v in Graph
  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      if (&maze->grid[i][j] != maze->start) {
        prev[i][j].x = -1;
        prev[i][j].y = -1;
        dist[i][j] = INT_MAX;
      }
    }
  }

  heapPush(&heap, maze->start, 0);
  prev[maze->start->y][maze->start->x].x = -1;
  prev[maze->start->y][maze->start->x].y = -1;
  dist[maze->start->y][maze->start->x] = 0;

  while (heap.size != 0) {
    HeapNode minNode = extract_min(&heap);
    if (minNode.priority > dist[minNode.vertex->y][minNode.vertex->x]) {
      continue;
    }

    if (minNode.vertex->visited) {
      continue;
    }

    minNode.vertex->visited = 1;
    totalSteps++;

    for (size_t i = 0; i < 4; ++i) {
      int neighbourX = (int)minNode.vertex->x + directionX[i];
      int neighbourY = (int)minNode.vertex->y + directionY[i];

      if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
          neighbourY < (int)maze->height) {
        Vertex* neighbor = &maze->grid[neighbourY][neighbourX];
        if (neighbor->is_wall || neighbor->visited) {
          continue;
        }

        // 1 as maze is unweighted
        int alt = minNode.priority + 1;
        if (alt < dist[neighbourY][neighbourX]) {
          prev[neighbourY][neighbourX].x = (int)minNode.vertex->x;
          prev[neighbourY][neighbourX].y = (int)minNode.vertex->y;

          dist[neighbourY][neighbourX] = alt;

          // parent pointer for retrace path
          maze->grid[neighbourY][neighbourX].parent = minNode.vertex;

          heapPush(&heap, &maze->grid[neighbourY][neighbourX], alt);
          // Q.decrease_priority(v, alt);
        }
      }
    }
  }

  if (maze->end && dist[maze->end->y][maze->end->x] != INT_MAX) {
    return DIJKSTRA_SUCCESS;
  }

  return DIJKSTRA_FAILURE;
}
