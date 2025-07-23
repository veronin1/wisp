#ifndef MAZE_PARSE_H
#define MAZE_PARSE_H

#include <stddef.h>
#define MAX_WIDTH 100
#define MAX_HEIGHT 100

typedef struct Vertex {
  size_t x;
  size_t y;
  int is_wall;
  int visited;
  struct Vertex *parent;
} Vertex;

typedef struct {
  Vertex grid[MAX_HEIGHT][MAX_WIDTH];
  size_t width;
  size_t height;
} Maze;

int load_maze(const char *filename, Maze *maze);

#endif
