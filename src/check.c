#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "chio.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./check filename\n");
        return -1;
    }
    char* filename = argv[1];
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("File not found.\n");
        return -1;
    }
    // Read the data and hash
    char* data = NULL;
    size_t n = 0;
    int err = chio_read(&data, &n, f);
    free(data);
    fclose(f);
    // Output whether file may be damaged
    if (err != 0) {
        printf("Corrupted.\n");
    } else {
        printf("OK.\n");
    }
    return err;
}
