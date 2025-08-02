#include <limits.h>
#include "dijkstra.h"
#include "maze.h"

#define MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

#define DIJKSTRA_SUCCESS 1
#define DIJKSTRA_FAILURE 0

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

int prev[MAX_HEIGHT][MAX_WIDTH];
int dist[MAX_HEIGHT][MAX_WIDTH];

int dijkstra(Maze* maze) {
  MinHeap heap;
  heap.size = 0;

  push(&heap, maze->start, 0);
  dist[maze->start->y][maze->start->x] = 0;

  // for each vertex  v in Graph
  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      if (&maze->grid[i][j] != maze->start) {
        prev[i][j] = -1;
        dist[i][j] = INT_MAX;
        push(&heap, &maze->grid[i][j], dist[i][j]);
      }
    }

    while (heap.size != 0) {
      HeapNode minNode = extract_min(&heap);
      Vertex* minVertex = minNode.vertex;

      for (size_t i = 0; i < 4; ++i) {
        int neighbourX = (int)minVertex->x + directionX[i];
        int neighbourY = (int)minVertex->y + directionY[i];

        if (neighbourX >= 0 && neighbourX < (int)maze->width &&
            neighbourY >= 0 && neighbourY < (int)maze->height) {
          Vertex* neighbourVert = &maze->grid[neighbourY][neighbourX];
          HeapNode* tmp = &heap.data[neighbourY][neighbourX];
          // 1 as maze is unweighted
          int alt = minNode.distance + 1;
          if (alt < tmp->distance) {
          }
        }
      }
    }

    return DIJKSTRA_SUCCESS;
  }

  HeapNode extract_min(MinHeap * heap) {
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

  void heapify_down(MinHeap * heap, size_t index) {
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

  void heapify_up(MinHeap * heap, size_t index) {
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

  int push(MinHeap * heap, Vertex * vertex, int distance) {
    if ((int)heap->size == MAX_HEAP_SIZE) {
      return DIJKSTRA_FAILURE;
    }

    heap->data[heap->size].vertex = vertex;
    heap->data[heap->size].distance = distance;
    heapify_up(heap, heap->size);
    heap->size++;
    return DIJKSTRA_SUCCESS;
  }
