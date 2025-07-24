#include <stdio.h>
#include <string.h>

#include <bfs.h>
#include "dfs.h"
#include "maze_parse.h"

int validate_input(int argc, char* argv[]);

int main(int argc, char* argv[]) {
  if (!validate_input(argc, argv)) {
    return 1;
  }

  Maze maze = {0};
  int result = load_maze(argv[1], &maze);
  if (result != 0) {
    printf("Failed to load maze from file '%s' with error code %d\n", argv[1],
           result);
    return 2;
  }

  if (strcmp(argv[1], "bfs") == 0) {
    if (bfs(&maze)) {
      print_maze(&maze);
    } else {
      printf("No path found\n");
    }
  } else if (strcmp(argv[1], "dfs") == 0) {
    if (dfs(&maze)) {
      print_maze(&maze);
    } else {
      printf("No path found\n");
    }
  }

  return 0;
}

int validate_input(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage: %s (-bfs|-dfs) <maze_file>\n", argv[0]);
    return 1;
  }

  char* type = argv[1];

  if ((strcmp(type, "-bfs") != 0) && (strcmp(type, "-dfs") != 0)) {
    printf("Invalid search type. Use -bfs or -dfs.\n");
    return 1;
  }
  return 0;
}
