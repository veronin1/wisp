#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Vertex {
    int x;
    int y;
    int is_wall;
    int visited;
    struct Vertex *parent;
} Vertex;

enum {
MAX_WIDTH = 100,
MAX_HEIGHT = 100
};

Vertex maze[MAX_HEIGHT][MAX_WIDTH];
int maze_width = 0;
int maze_height = 0;


int read_file(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }


    FILE* maze_file = fopen(argv[1], "r");
    if (!maze_file) {
        printf("Error opening file %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    char buffer[MAX_HEIGHT + 2]; // room for newline and null terminator
    while (fgets(buffer, sizeof(buffer), maze_file)) {
        ++maze_height;
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (maze_height == 0) {
            maze_width = strlen(buffer);
        } else {
            if (strlen(buffer) != maze_width) {
                printf("Inconsistent line lengths in %s", argv[1]);
            }
        }

        for (size_t x = 0, string_length = strlen(buffer); x < string_length; ++x) {
            maze[maze_height][x].x = buffer[x];
            maze[maze_height][x].y = maze_height;
            maze[maze_height][x].is_wall = (buffer[x] = '#') ? 1 : 0;
            maze[maze_height][x].visited = 0;

        }
    }


}
