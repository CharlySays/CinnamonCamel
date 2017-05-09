#include "grid.h"

bool culCheck(Field grid[][9]);
bool rowCheck(Field grid[][9]);
bool squareCheck(Field grid[][9]);

bool squareCheckField(Field grid[][9], int x, int y);
bool culCheckField(Field grid[][9],int x, int y);
bool rowCheckField(Field grid[][9], int x, int y);

bool winCondition(Field grid[][9]);
