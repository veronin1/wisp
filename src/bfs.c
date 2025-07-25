#include "bfs.h"
#include "maze.h"

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

size_t bfs(Maze* maze) {
  VertexQueue queue;
  queue.front = 0;
  queue.rear = 0;
  queue.size = 0;
  queue.capacity = (size_t)MAX_WIDTH * MAX_HEIGHT;
  queue.data[queue.rear++] = maze->start;
  queue.size++;
  maze->start->visited = 1;

  size_t steps = 0;

  while (queue.size != 0) {
    Vertex* current = dequeue(&queue);

    if (!current) {
      continue;
    }
    if (current == maze->end) {
      return steps;
    }

    for (size_t i = 0; i < 4; ++i) {
      int neighbourX = (int)current->x + directionX[i];
      int neighbourY = (int)current->y + directionY[i];

      if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
          neighbourY < (int)maze->height) {
        Vertex* neighbour = &maze->grid[neighbourY][neighbourX];

        if (!neighbour->visited && !neighbour->is_wall) {
          neighbour->visited = 1;
          neighbour->parent = current;
          enqueue(&queue, neighbour);
        }
      }
    }
    ++steps;
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

void enqueue(VertexQueue* queue, Vertex* element) {
  if (queue->size == queue->capacity) {
    return;
  }

  if (queue->size == 0) {
    queue->front = queue->rear = 0;
  } else {
    queue->rear = (queue->rear + 1) % queue->capacity;
  }

  queue->data[queue->rear] = element;
  queue->size++;
}
