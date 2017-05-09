#include "logic.h"
#include "global.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];

int solvePuzzle(int row, int column);
void printPuzzle();
void removeNNumbers( int numbers);
void prepareForGUI();
void generateGrid(int numFields);
int isValid(int row, int column, int number);
