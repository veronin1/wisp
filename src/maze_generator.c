#include "maze_generator.h"
#include <stdint.h>
#include <time.h>
#include "maze.h"

void maze_generator(size_t size) {
  Maze maze;

  if (size > MAX_HEIGHT || size > MAX_WIDTH) {
    return;
  }

  maze.width = maze.height = size;

  for (size_t pos_y = 0; pos_y < maze.height; ++pos_y) {
    for (size_t pos_x = 0; pos_x < maze.width; ++pos_x) {
      maze.grid[pos_y][pos_x].parent = NULL;
      maze.grid[pos_y][pos_x].is_wall = 1;
      maze.grid[pos_y][pos_x].visited = 0;
      maze.grid[pos_y][pos_x].y = pos_y;
      maze.grid[pos_y][pos_x].x = pos_x;
    }
  }
}

/* seed with current time
shift left by numberOfShift bits
perform bitwise xor
*/
void random_number_generator(void) {
  const size_t numberOfShits = 13;
  // seed
  time_t currentTime = time(NULL);
  int64_t originalSeed = (int64_t)currentTime;

  int64_t newSeed = originalSeed << numberOfShits;

  newSeed = newSeed ^ originalSeed;
}
