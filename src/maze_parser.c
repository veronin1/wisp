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


    char buffer[MAX_HEIGHT];
    FILE* maze_file = fopen(argv[1], "r");
    if (maze_file) {
        while (fgets(buffer, sizeof(buffer), maze_file)) {
            ++maze_height;
        }
    } else {
        printf("Error opening file %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

}
