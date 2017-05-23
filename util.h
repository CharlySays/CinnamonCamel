#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * @FUNCTION itoa
 *
 * Convert an integer to an string.
 * For a human readable number use the base 10.
 *
 * @PARAMETERS
 * 	int value       - This value will be converted
 *      char* result    - To store the result
 *      int base        - Base of value
 *
 */

char* itoa(int value, char* result, int base);

/**
 * @FUNCTION isValueInArray
 *
 * Check whether array contains value
 *
 * @PARAMETERS
 * 	int value       - Is this value contained
 *      int* array      - In this array
 *      int size        - With this array-length
 *
 */

int isValueInArray(int value, int *array, int size);

#endif /* UTIL_H */