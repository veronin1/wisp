#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "maze.h"

#define MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

#define HEAP_SUCCESS 1
#define HEAP_FAILURE 0

typedef struct {
  Vertex *vertex;
  int priority;
} HeapNode;

typedef struct {
  HeapNode data[MAX_HEAP_SIZE];
  size_t size;
} MinHeap;

HeapNode extract_min(MinHeap *heap);
void decrease_priority(Vertex* vertex, int distance);
void heapify_down(MinHeap *heap, size_t index);
void heapify_up(MinHeap *heap, size_t index);
int heapPush(MinHeap *heap, Vertex* vertex, int distance);

#endif // MIN_HEAP.H
