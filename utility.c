#include "utility.h"

void * myMalloc(size_t size) {
    void * p = malloc(size);

    if (p == NULL) {
        perror("Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    return p;
}
