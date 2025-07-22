#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int is_wall;
    int visited;
    struct Vertex *parent;
} Vertex;

int read_file(int argc, char* argv[]) {
    FILE* maze = fopen(argv[1], "r");
    if (!maze) {
        printf("Error opening file &s\n"), strerror(errno);
    }

}
