#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>

bool validNum(int value);
char* itoa(int value, char* result, int base);
int isValueInArray(int value, int *array, int size);

#endif /* UTIL_H */

