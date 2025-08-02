#include <limits.h>
#include "dijkstra.h"
#include "maze.h"

#define MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

#define DIJKSTRA_SUCCESS 1
#define DIJKSTRA_FAILURE 0

int dijkstra(Maze* maze) {
  MinHeap heap;
  heap.size = 0;

  push(&heap, maze->start, 0);

  // for each vertex v in graph.vertices
  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      Vertex* currentVertex = &maze->grid[i][j];
      int dist = INT_MAX;
      if (!currentVertex->is_wall) {
        push(&heap, currentVertex, dist);
      }
    }
  }

  return DIJKSTRA_SUCCESS;
}

HeapNode extract_min(MinHeap* heap) {
  if (heap->size == 0) {
    HeapNode emptyNode = {0};
    return emptyNode;
  }

  HeapNode min = heap->data[0];
  heap->data[0] = heap->data[heap->size - 1];
  heap->size--;
  heapify_down(heap, 0);
  return min;
}

void heapify_down(MinHeap* heap, size_t index) {
  while (1) {
    size_t leftChild = (2 * index) + 1;
    size_t rightChild = (2 * index) + 2;
    size_t selected = index;

    if (leftChild < heap->size &&
        heap->data[leftChild].distance < heap->data[selected].distance) {
      selected = leftChild;
    }

    if (rightChild < heap->size &&
        heap->data[rightChild].distance < heap->data[selected].distance) {
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

void heapify_up(MinHeap* heap, size_t index) {
  if (index == 0) {
    return;
  }

  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (heap->data[index].distance < heap->data[parent].distance) {
      HeapNode tmp = heap->data[index];
      heap->data[index] = heap->data[parent];
      heap->data[parent] = tmp;
      index = parent;
    } else {
      break;
    }
  }
}

int push(MinHeap* heap, Vertex* vertex, int distance) {
  if ((int)heap->size == MAX_HEAP_SIZE) {
    return DIJKSTRA_FAILURE;
  }

  heap->data[heap->size].vertex = vertex;
  heap->data[heap->size].distance = distance;
  heapify_up(heap, heap->size);
  heap->size++;
  return DIJKSTRA_SUCCESS;
}
