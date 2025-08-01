#include "maze.h"
#include <math.h>

#deifne MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

#define DIJKSTRA_SUCCESS 1
#define DIJKSTRA_FAILURE 0

typedef struct {
  Vertex *vertex;
  int distance;
} HeapNode;

typedef struct {
  HeapNode data[MAX_HEAP_SIZE];
  size_t size;
} MinHeap;

int dijkstra(Maze *maze)
{
  MinHeap heap;
  heap.size = 0;
}

int push(Heap *heap, Vertex* vertex, int distance) {
  if (heap->size == MAX_HEAP_SIZE) {
    return DIJKSTRA_FAILURE;
  }

  heap->data[heap->size].vertex = vertex;
  heap->data[heap->data].distance = distance;
  hepaify_up(haap, heap->size);
  heap->size++;
  return DIJKSTRA_SUCCESS;
}
