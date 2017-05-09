#include "logic.h"
#include "global.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];

int isValid(int row, int column, int number);
int solvePuzzle(int row, int column);
void printPuzzle();
void removeNNumbers(int numbers);
void prepareForGUI();
void generateGrid(int numFields);
