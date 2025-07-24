#include "bfs.h"
#include "maze.h"

int bfs(Maze* maze) {
  VertexQueue queue;
  queue.front = 0;
  queue.rear = 0;
  queue.size = 0;
  queue.capacity = MAX_WIDTH * MAX_HEIGHT;
  queue.data[queue.rear++] = maze->start;
  queue.size++;

  while (queue.size > 0) {
    Vertex* current = dequeue(&queue);
  }
  return 0;
}

Vertex* dequeue(VertexQueue* queue) {
  if (queue->size == 0) {
    return NULL;
  }
  Vertex* front = queue->data[queue->front];

  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;
  return front;
}
