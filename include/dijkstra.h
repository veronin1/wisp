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
HeapNode extract_min(MinHeap *heap);
void decrease_priority(Vertex* vertex, int distance);
void heapify_down(MinHeap *heap, size_t index);
void heapify_up(MinHeap *heap, size_t index);
int push(MinHeap *heap, Vertex* vertex, int distance);

#endif
