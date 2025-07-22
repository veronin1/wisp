#include <errno.h>
#include <stdio.h>
#include <string.h>

int read_file(int argc, char* argv[]) {
    FILE* maze = fopen(argv[1], "r");
    if (!maze) {
        printf("Error opening file &s\n"), strerror(errno);
    }
}
