#include <stdio.h>
#include <string.h>

#include "bfs.h"
#include "dfs.h"
#include "dijkstra.h"
#include "globals.h"
#include "maze_generator.h"
#include "maze_parse.h"
#include "retrace_path.h"

int validate_input(int argc, char* argv[]);

const char* algorithms[3] = {"-bfs", "-dfs", "-dijkstra"};
const size_t algorithmsSize = 3;

int main(int argc, char* argv[]) {
  if (!validate_input(argc, argv)) {
    return 1;
  }

  /*
  Maze maze = {0};
  int result = load_maze(argv[2], &maze);
  if (result != 0) {
    printf("Failed to load maze from file '%s' with error code %d\n", argv[2],
           result);
    return 2;
  }
    */

  const size_t mazeSize = 25;
  Maze maze = dfs_maze_generate(mazeSize);
  reset_visited(&maze);

  if (strcmp(argv[1], "-bfs") == 0) {
    if (bfs(&maze)) {
      if (maze.end != NULL) {
        size_t pathSteps = retrace_path(maze.end, &maze);
        if (totalSteps >= 0) {
          printf("===== BFT =====\n");
          printf("Total Steps Taken %zu\n", totalSteps);
          printf("Found Path Steps: %zu\n", pathSteps);
          printf("=== Solution ===\n");
          print_maze(&maze);
        }
      }
    } else {
      printf("No path found\n");
    }
  } else if (strcmp(argv[1], "-dfs") == 0) {
    if (dfs(&maze)) {
      if (maze.end != NULL) {
        size_t pathSteps = retrace_path(maze.end, &maze);
        if (totalSteps >= 0) {
          printf("=== DFT ===\n");
          printf("Total Steps Taken %zu\n", totalSteps);
          printf("Found Path Steps: %zu\n", pathSteps);
          printf("=== Solution ===\n");
          print_maze(&maze);
        }
      } else {
        printf("No path found\n");
      }
    }
  } else if (strcmp(argv[1], "-dijkstra") == 0) {
    if (dijkstra(&maze)) {
      if (maze.end != NULL) {
        size_t pathSteps = retrace_path(maze.end, &maze);
        if (totalSteps >= 0) {
          printf("=== DIJKSTRA ===\n");
          printf("Total Steps Taken %zu\n", totalSteps);
          printf("Found Path Steps: %zu\n", pathSteps);
          printf("=== Solution ===\n");
          print_maze(&maze);
        }
      } else {
        printf("No path found\n");
      }
    }

    return 0;
  }

  int validate_input(int argc, char* argv[]) {
    if (argc != 3) {
      printf("Usage: %s ( -bfs| -dfs| -dijkstra) <maze_file>\n", argv[0]);
      return 0;
    }

    char* type = argv[1];

    if ((strcmp(type, "-bfs") != 0) && (strcmp(type, "-dfs") != 0) &&
        (strcmp(type, "-dijkstra") != 0)) {
      printf("Invalid search type. Use -bfs, -dfs or -dijkstra.\n");
      return 0;
    }
    return 1;
  }
