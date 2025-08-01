#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "maze.h"

#define MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

typedef struct {
  Vertex *vertex;
  int distance;
} HeapNode;

typedef struct {
  HeapNode data[MAX_HEAP_SIZE];
  size_t size;
} MinHeap;

int dijkstra(Maze *maze);
void heapify_up(Heap *heap, size_t index);
int push(Heap *heap, Vertex* vertex, int distance);

#endif
