#include "grid.h"

#include "global.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];
int gameTime;

void gridToFile(char* fileName);
bool readGridWithFile(char *fileName, int numberOfFields);
