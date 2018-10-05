/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

void * myMalloc(size_t size);
void * myCalloc(size_t nitems, size_t size);
void myExit(char *errorMessage);

/* Checks that a string is a positive non zero integer */
Boolean isPosIntNonZero(char *num);

/* Checks that a string is a positive integer*/
Boolean isPosInt(char *num);

/* Checks that a string contains only digits */
Boolean isNumber(char *num);
#endif
