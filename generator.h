#include "logic.h"
#include <time.h>


int isValid(Field grid[][9], int row, int column, int number);
int solvePuzzle(Field grid[][9], int row, int column);
void printPuzzle(Field grid[][9]);
void removeNNumbers(Field grid[][9], int numbers);
void prepareForGUI(Field grid[][9]);
void generateGrid(Field grid[][9], int numFields);