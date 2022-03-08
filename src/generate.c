#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "chio.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./generate filename num_bytes\n");
        return 1;
    }
    char* filename = argv[1];
    int n = atoi(argv[2]);
    assert(n > 0);

    // Generate n bytes of random data
    char data[n];
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 255;
    }

    // Write data to file
    FILE* f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Couldn't open file.\n");
        return 1;
    }
    chio_write(f, data, n);
    fclose(f);
    return 0;
}
