#includ "maze.h"

#deifne MAX_HEAP_SIZE (MAX_WIDTH * MAX_HEIGHT)

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
  
}
