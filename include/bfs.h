#ifndef BFS_H
#define BFS_H

#include "maze.h"

#define BFS_SUCCESS 0
#define BFS_FAILURE -1

typedef struct {
  Vertex *data[MAX_WIDTH * MAX_HEIGHT];
  size_t front;
  size_t rear;
  size_t size;
  size_t capacity;
} VertexQueue;

int bfs(Maze *maze);
Vertex *dequeue(VertexQueue *queue);
int enqueue(VertexQueue *queue, Vertex *element);
void reset_visited(Maze *maze);

#endif // BFS.H
