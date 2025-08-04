#include "a_star.h"
#include "maze.h"
#include "min_heap.h"

#include <limits.h>
#include <stdlib.h>

int distance[MAX_HEIGHT][MAX_WIDTH];
int heuristic[MAX_HEIGHT][MAX_WIDTH];

typedef struct {
  int g_score;
  int h_score;
} AStar;

int a_star(Maze* maze) {
  MinHeap open_set;
  open_set.size = 0;

  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      distance[i][j] = INT_MAX;
    }
  }

  distance[maze->start->y][maze->start->x] = 0;
  int h = calculate_heuristic(maze->start, maze->end);
  heapPush(&open_set, maze->start, h);

  while (open_set.size != 0) {
    HeapNode current = extract_min(&open_set);
  }

  return A_STAR_SUCCESS;
}

// use manhattan distance (taxicab distance)
int calculate_heuristic(Vertex* start, Vertex* end) {
  return abs((int)start->x - (int)end->x) + abs((int)start->y - (int)end->y);
}
