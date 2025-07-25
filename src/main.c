#include <stdio.h>
#include <string.h>

#include "bfs.h"
#include "dfs.h"
#include "maze_parse.h"
#include "retrace_path.h"

int validate_input(int argc, char* argv[]);

int main(int argc, char* argv[]) {
  if (!validate_input(argc, argv)) {
    return 1;
  }

  Maze maze = {0};
  int result = load_maze(argv[2], &maze);
  if (result != 0) {
    printf("Failed to load maze from file '%s' with error code %d\n", argv[2],
           result);
    return 2;
  }

  if (strcmp(argv[1], "-bfs") == 0) {
    size_t totalSteps = bfs(&maze);
    if (maze.end != NULL) {
      size_t pathSteps = retrace_path(maze.end, &maze);
      if (totalSteps >= 0) {
        printf("Total Steps Taken %zu\n", totalSteps);
        printf("Path Steps: %zu\n", pathSteps);
        // print_maze(&maze);
      }
    } else {
      printf("No path found\n");
    }
  } else if (strcmp(argv[1], "-dfs") == 0) {
    size_t totalSteps = dfs(&maze);
    if (maze.end != NULL) {
      size_t pathSteps = retrace_path(maze.end, &maze);
      if (totalSteps >= 0) {
        printf("Total Steps Taken %zu\n", totalSteps);
        printf("Path Steps: %zu\n", pathSteps);
        // print_maze(&maze);
      } else {
        printf("No path found\n");
      }
    }
  }

  return 0;
}

int validate_input(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Usage: %s (-bfs|-dfs) <maze_file>\n", argv[0]);
    return 0;
  }

  char* type = argv[1];

  if ((strcmp(type, "-bfs") != 0) && (strcmp(type, "-dfs") != 0)) {
    printf("Invalid search type. Use -bfs or -dfs.\n");
    return 0;
  }
  return 1;
}
