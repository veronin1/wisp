#ifndef A_STAR_H
#define A_STAR_H

#include "maze.h"

#define A_STAR_SUCCESS 0
#define A_STAR_FAILURE -1

int a_star(Maze* maze);
int calculate_heuristic(Vertex* start, Vertex* end);

#endif
