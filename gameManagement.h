#include "grid.h"

#include "global.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];

void gridToFile(char* fileName);
bool readGridWithFile(FILE *myFile);
