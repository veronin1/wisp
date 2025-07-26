#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"
#include <stddef.h>
#include <stdint.h>

Maze dfs_maze_generate(size_t size);
void dfs_maze_generate_cell(Maze *maze, size_t posX, size_t posY);
int64_t random_number_generator(void);
#endif
