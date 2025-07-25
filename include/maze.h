#ifndef MAZE_H
#define MAZE_H

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000

#include <stddef.h>

typedef struct Vertex {
  size_t x;
  size_t y;
  int is_wall;
  int visited;
  int on_path;
  struct Vertex *parent;
} Vertex;

typedef struct {
  Vertex grid[MAX_HEIGHT][MAX_WIDTH];
  size_t width;
  size_t height;
  Vertex *start;
  Vertex *end;
} Maze;

#endif
