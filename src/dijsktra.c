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

  push(heap, maze->start, 0);

  // for each vertex v in grapch.vertices
  
}

HeapNode extract_min(Heap *heap) {
  HeapNode *min = heap->data[0];
  heap->data[0] = heap->data[heap->size - 1];
  heap->size--;
  heapify_down(heap, 0);
  return min;
}

void heapify_down(Heap *heap, size_t index) {
    while (1) {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;
        size_t selected = index;

        if (leftChild < heap->size && heap->data[leftChild].distance < heap->data[selected].distance) {
            selected = leftChild;
        }

        if (rightChild < heap->size && heap->data[rightChild].distance < heap->data[selected].distance) {
            selected = rightChild;
        }

        if (selected == index) {
            break;
        }

        HeapNode tmp = heap->data[selected];
        heap->data[selected] = heap->data[index];
        heap->data[index] = tmp;

        index = selected;
    }
}

void heapify_up(Heap *heap, size_t index) {
  if (index == 0) {
    return;
  }

  while (index > 0) {
    int parent = (index - 1) / 2;
    if (heap->data[index].distance < heap->data[parent].distance) {
      HeapNode tmp = heap->data[index];
      heap->data[index] = heap->data[parent]
      heap->data[parent] = tmp;
      index = parent;
    } else {
      break;
    }
  }
}

int push(Heap *heap, Vertex* vertex, int distance) {
  if (heap->size == MAX_HEAP_SIZE) {
    return DIJKSTRA_FAILURE;
  }

  heap->data[heap->size].vertex = vertex;
  heap->data[heap->size].distance = distance;
  hepaify_up(heap, heap->size);
  heap->size++;
  return DIJKSTRA_SUCCESS;
}
