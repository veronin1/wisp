#include <stdio.h>

#include "dfs.h"
#include "maze.h"
#include "maze_parse.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <maze_file>\n", argv[0]);
    return 1;
  }

  Maze maze = {0};
  int result = load_maze(argv[1], &maze);
  if (result != 0) {
    printf("Failed to load maze from file '%s' with error code %d\n", argv[1],
           result);
    return 1;
  }

  if (dfs(&maze)) {
    print_maze(&maze);
  } else {
    printf("No path found\n");
  }

  return 0;
}
