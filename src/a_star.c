#include "a_star.h"
#include <stdlib.h>
#include "maze.h"
#include "min_heap.h"

int distance[MAX_HEIGHT][MAX_WIDTH];
int heuristic[MAX_HEIGHT][MAX_WIDTH];

int a_star(Maze* maze) {
  MinHeap aStarHeap;
  aStarHeap.size = 0;

  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      distance[i][j] = 0;
      heapPush(&aStarHeap, &maze->grid[i][j], 1);
    }
  }

  int priority;

  while (aStarHeap.size != 0) {
  }

  return A_STAR_SUCCESS;
}

int calculate_heuristic(Vertex* start, Vertex* end) {
  int heuristic =
      abs((int)start->x - (int)end->x) + abs((int)start->y - (int)end->y);

  return heuristic;
}
