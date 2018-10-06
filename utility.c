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


Boolean isPosIntNonZero(char *num) {
	if (isNumber(num)) {
		if (atoi(num) > 0)
			return TRUE;
	}
	return FALSE;
}


Boolean isPosInt(char *num) {
	if (isNumber(num)) {
		if (atoi(num) >= 0)
			return TRUE;
	}
	return FALSE;
}


void myExit(char *errorMessage) {
	printf(errorMessage);
	exit(EXIT_FAILURE);
}


Boolean isNumber(char *num) {
	int i = 0;
	char currChar = num[i];

	while (currChar != '\0') {
		if (!isdigit(currChar)) {
			return FALSE;
		}
		i++;
		currChar = num[i];
	}
	return TRUE;
}
