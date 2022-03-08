#ifndef _CHIO
#define _CHIO

#include <stdio.h>

int chio_write(FILE* f, const char* data, size_t n);
int chio_read(char** data, size_t* n, FILE* f);

#endif