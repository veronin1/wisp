#include "maze_generator.h"
#include "maze.h"

void maze_generator(size_t size) {
  Maze maze;

  if (size > MAX_HEIGHT || size > MAX_WIDTH) {
    return;
  }

  maze.width = maze.height = size;
}
