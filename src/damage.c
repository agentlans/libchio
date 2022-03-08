#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "chio.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./damage filename\n");
        return -1;
    }
    char* filename = argv[1];
    FILE* f = fopen(filename, "r+b");
    if (!f) {
        fprintf(stderr, "File not found.\n");
        return -1;
    }
    // Find the file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    if (size == 0) {
        fprintf(stderr, "File is empty.\n");
        fclose(f);
        return -1;
    }

    // The place where we want to damage
    long pos = rand() % size;
    fseek(f, pos, SEEK_SET);
    // Read the byte, change it, then write back.
    char byte;
    fread(&byte, 1, 1, f);
    byte++;
    fseek(f, -1, SEEK_CUR);
    fwrite(&byte, 1, 1, f);

    fclose(f);

    return 0;
}