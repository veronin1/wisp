#ifndef BFS_H
#define BFS_H

#include "maze.h"

typedef struct {
  Vertex *data[MAX_WIDTH * MAX_HEIGHT];
  int front;
  int rear;
  size_t size;
  size_t capacity;
} VertexQueue;

Vertex *dequeue(VertexQueue *queue);

#endif
