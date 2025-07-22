#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "maze_parse.h"

int load_maze(const char* filename, Maze* maze) {

    FILE* maze_file = fopen(filename, "r");
    if (!maze_file) {
        printf("Error opening file %s: %s\n", filename, strerror(errno));
        return 1;
    }

    char buffer[MAX_HEIGHT + 2]; // room for newline and null terminator
    size_t height = 0;

    while (fgets(buffer, sizeof(buffer), maze_file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        size_t width = strlen(buffer);

        if (height == 0) {
            maze->width = width;
        } else {
            if (strlen(buffer) != maze->width) {
                printf("Inconsistent line lengths in %s", filename);
                return 2;
            }
        }

        for (size_t col = 0, string_length = strlen(buffer); col < string_length; ++col) {
            maze->grid[height][col].x = col;
            maze->grid[height][col].y = height;
            maze->grid[height][col].is_wall = (buffer[col] == '#') ? 1 : 0;
            maze->grid[height][col].visited = 0;
            maze->grid[height][col].parent = NULL;
        }
        ++height;
    }
    maze->height = height;
    fclose(maze_file);
    return 0;
}
