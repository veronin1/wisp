#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze_parse.h"

int load_maze(const char* filename, Maze* maze) {
  FILE* maze_file = fopen(filename, "r");
  if (!maze_file) {
    printf("Error opening file %s: %s\n", filename, strerror(errno));
    return 1;
  }

  char buffer[MAX_HEIGHT + 2]; // room for newline and null terminator
  size_t height = 0;

  maze->start = NULL;
  maze->end = NULL;

  while (fgets(buffer, sizeof(buffer), maze_file)) {
    buffer[strcspn(buffer, "\r\n")] = 0;
    size_t width = strlen(buffer);

    if (height == 0) {
      maze->width = width;
    } else {
      if (strlen(buffer) != maze->width) {
        printf("Inconsistent line lengths in %s", filename);
        fclose(maze_file);
        return 2;
      }
    }

    for (size_t col = 0; col < width; ++col) {
      maze->grid[height][col].x = col;
      maze->grid[height][col].y = height;
      maze->grid[height][col].visited = 0;
      maze->grid[height][col].on_path = 0;
      maze->grid[height][col].parent = NULL;

      char current = buffer[col];
      switch (current) {
        case '#':
          maze->grid[height][col].is_wall = 1;
          break;
        case 'S':
          maze->grid[height][col].is_wall = 0;
          maze->start = &maze->grid[height][col];
          break;
        case 'E':
          maze->grid[height][col].is_wall = 0;
          maze->end = &maze->grid[height][col];
          break;
        default:
          maze->grid[height][col].is_wall = 0;
          break;
      }
    }
    ++height;
  }

  maze->height = height;

  if (!maze->start || !maze->end) {
    if (!maze->start) {
      printf("Error: Maze has no start point 'S'\n");
    }
    if (!maze->end) {
      printf("Error: Maze has no end point 'E'\n");
    }
    fclose(maze_file);
    return 3;
  }

  fclose(maze_file);
  return 0;
}

void print_maze(const Maze* maze) {
  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      const Vertex* current = &maze->grid[i][j];
      if (current == maze->start) {
        putchar('S');
      } else if (current == maze->end) {
        putchar('E');
      } else if (current->is_wall) {
        putchar('#');
      } else if (current->visited) {
        putchar('.');
      } else {
        putchar(' ');
      }
    }
    putchar('\n');
  }
}
