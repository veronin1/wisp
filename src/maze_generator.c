#include "maze_generator.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "maze.h"

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

Maze dfs_maze_generate(size_t size) {
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

  srand((uint)random_number_generator());
  size_t startX = (size_t)rand() % maze.width;
  size_t startY = (size_t)rand() % maze.height;

  dfs_maze_generate_cell(&maze, startX, startY);

  return maze;
}

void dfs_maze_generate_cell(Maze* maze, size_t posX, size_t posY) {
  Vertex* current = &maze->grid[posY][posX];
  current->visited = 1;
  current->is_wall = 0;

  int directions[4] = {0, 1, 2, 3};
  for (size_t i = 3; i > 0; --i) {
    int randomIndex = rand() % ((int)i + 1);
    int temp = directions[i];
    directions[i] = directions[randomIndex];
    directions[randomIndex] = temp;
  }

  for (size_t i = 0; i < 4; ++i) {
    int randomDirection = directions[i];
    int neighbourX = (int)current->x + (2 * directionX[randomDirection]);
    int neighbourY = (int)current->y + (2 * directionY[randomDirection]);
    int wallX = (int)current->x + directionX[randomDirection];
    int wallY = (int)current->y + directionY[randomDirection];

    if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
        neighbourY < (int)maze->height) {
      Vertex* neighbour = &maze->grid[neighbourY][neighbourX];
      Vertex* intermediateNeighbour = &maze->grid[wallY][wallX];

      if (neighbour->visited == 0 && intermediateNeighbour->visited == 0) {
        neighbour->visited = 1;
        neighbour->is_wall = 0;
        intermediateNeighbour->is_wall = 0;

        dfs_maze_generate_cell(maze, (size_t)neighbourX, (size_t)neighbourY);
      }
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
