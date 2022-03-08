#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "murmur3.h"
#include "chio.h"

#define CHECK_WRITE if (ferror(f)) return 1;
#define CHECK_READ if (feof(f) || ferror(f)) return 1;

int chio_write(FILE* f, const char* data, size_t n) {
    unsigned int seed = rand();
    char hash[16]; // 128 bits
    fwrite(&seed, sizeof(unsigned int), 1, f);
    CHECK_WRITE
    // Compute the hash
    MurmurHash3_x64_128(data, n, seed, hash);
    fwrite(hash, 16, 1, f);
    CHECK_WRITE
    // Write the size and data
    fwrite(&n, sizeof(size_t), 1, f);
    CHECK_WRITE
    fwrite(data, 1, n, f);
    CHECK_WRITE
    return 0;
}

int chio_read(char** data, size_t* n, FILE* f) {
    unsigned int seed;
    char hash[16];
    fread(&seed, sizeof(unsigned int), 1, f);
    CHECK_READ
    fread(hash, 16, 1, f);
    CHECK_READ
    fread(n, sizeof(size_t), 1, f);
    CHECK_READ
    *data = malloc(*n);
    if (!*data) {return 1;}
    fread(*data, 1, *n, f);
    CHECK_READ

    // Compute hash and check that hash is correct
    char actual_hash[16];
    MurmurHash3_x64_128(*data, *n, seed, actual_hash);
    if (memcmp(actual_hash, hash, 16) == 0) {
        return 0;
    } else {
        return 1;
    }
}
