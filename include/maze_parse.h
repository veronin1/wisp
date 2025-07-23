#ifndef MAZE_PARSE_H
#define MAZE_PARSE_H

#include "maze.h"

int load_maze(const char *filename, Maze *maze);
void print_maze(const Maze *maze);

#endif
