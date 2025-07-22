#include <errno.h>
#include <stdio.h>
#include <string.h>

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
    FILE* maze = fopen(argv[1], "r");
    if (!maze) {
        printf("Error opening file &s\n", strerror(errno));
    }

}
