#include "maze_generator.h"
#include <time.h>
#include <unistd.h>
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

int64_t random_number_generator(void) {
  time_t currentTime = time(NULL);
  pid_t pid = getpid();
  int64_t seed = ((int64_t)currentTime) ^ (int64_t)(pid);

  /*clamp iterations to 5-19
  and shiftAmount to 1-63 */
  const size_t iterations = (size_t)(pid % 15) + 5;
  const size_t shiftAmount = (size_t)(currentTime % 63) + 1;

  for (size_t i = 0; i < iterations; ++i) {
    if (i % 2 == 0) {
      seed ^= seed >> shiftAmount;
    } else {
      seed ^= seed << shiftAmount;
    }
  }
  return seed;
}
