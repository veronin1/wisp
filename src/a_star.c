#include "a_star.h"
#include "min_heap.h"

int a_star(Maze* maze) {
  MinHeap aStarHeap;
  aStarHeap.size = 0;

  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      heapPush(&aStarHeap, &maze->grid[i][j], 1);
    }
  }

  return A_STAR_SUCCESS;
}
