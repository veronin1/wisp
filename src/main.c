#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfs.h"
#include "dfs.h"
#include "dijkstra.h"
#include "globals.h"
#include "maze.h"
#include "maze_generator.h"
#include "maze_parse.h"
#include "retrace_path.h"

int validate_input(int argc, char* argv[]);

const char* algorithms[3] = {"-bfs", "-dfs", "-dijkstra"};
const size_t algorithmsSize = 3;

int main(int argc, char* argv[]) {
  if (validate_input(argc, argv) != 0) {
    return 1;
  }

  Maze maze = {0};

  if (strcmp(argv[1], "-gen") == 0) {
    const size_t mazeSize = (size_t)strtoull(argv[2], NULL, 10);
    maze = dfs_maze_generate(mazeSize);
    maze_to_file(&maze, argv[3]);
    reset_visited(&maze);
    return 0;
  }

  int result = load_maze(argv[2], &maze);
  if (result != 0) {
    printf("Failed to load maze from file '%s' with error code %d\n", argv[2],
           result);
    return 2;
  }

  if (strcmp(argv[1], "-bfs") == 0) {
    if (bfs(&maze)) {
      if (maze.end != NULL) {
        size_t pathSteps = retrace_path(maze.end, &maze);
        if (totalSteps >= 0) {
          printf("===== BFT =====\n");
          printf("Total Steps Taken %zu\n", totalSteps);
          printf("Found Path Steps: %zu\n", pathSteps);
          printf("=== Solution ===\n");
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
}

int validate_input(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage:\n");
    printf("  %s ( -bfs | -dfs | -dijkstra) <maze_file>\n", argv[0]);
    printf("  %s -gen <size> <maze_file>\n", argv[0]);
    return 1;
  }

  char* type = argv[1];

  // Maze generation
  if (strcmp(type, "-gen") == 0) {
    if (argc != 4) {
      printf("Usage: %s -gen <size> <file_to_create>", argv[0]);
      return 1;
    }

    char* sizeOfMaze = argv[2];
    for (size_t i = 0; sizeOfMaze[i]; ++i) {
      if (!isdigit((unsigned int)sizeOfMaze[i])) {
        printf("Error: Size must be a positive number");
        return 1;
      }
    }

    return 0;
  }

  // Searching algorithms
  if (strcmp(type, "-bfs") == 0 || strcmp(type, "-dfs") == 0 ||
      strcmp(type, "-dijkstra") == 0) {
    if (argc != 3) {
      printf("Error: %s requires one argument (maze file).\n", type);
      return 1;
    }

    return 0;
  }

  printf("Invalid command. Use -bfs, -dfs, -dijkstra or -gen");
  return 1;
}
