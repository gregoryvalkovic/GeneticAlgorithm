#include "utility.h"

void * myMalloc(size_t size) {
    void * p = malloc(size);

    if (p == NULL) {
        perror("Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    return p;
}


void * myCalloc(size_t nitems, size_t size) {
    void * p = calloc(nitems, size);

    if (p == NULL) {
        perror("Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    return p;
}
