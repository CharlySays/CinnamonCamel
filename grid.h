#ifndef GRID_H
#define GRID_H

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "util.h"

typedef struct{
    int value;
    char show[10];
    bool correct;
    bool fixed;
    char normalState[100];
    GtkWidget* button;
}Field;

void render(Field grid[][9] ,int X, int Y);
void renderInt(Field grid[][9] ,int X, int Y);

bool readGrid(Field grid[][9]);
char* itoa(int value, char* result, int base);
bool insertValue(Field grid[][9], int value, int X, int Y);
bool isfixed(Field grid[][9], int X, int Y);

#endif /* GRID_H */
