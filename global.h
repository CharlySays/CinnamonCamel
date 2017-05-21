#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "util.h"

/*****          
                This Header includes all shared global variables        
                Therefore is in front of the variables an "extern".
                It allows to access this variables from anywhere else
                if this header is included
                                                                        *****/

/*****                  GLOBAL STRUCTURE TO STORE SUDOKU                *****/

typedef struct{
    int value;                  // unit value
    char show[10];              // for Graphical User Interface
    bool fixed;                 // System set field?
    char normalState[100];      // For the .css style
    GtkWidget* button;          // every unit is a button
}Field;

/*****
                        GLOBAL VARIABLES                                *****/

extern gpointer last;               // Id from the last clicked/pressed unit

extern GtkWidget *lastWidget;       // Pointer on the last clicked/pressed
                                    // unit
extern GtkWidget *entry;            // Pointer on the read-in entry-widget
extern GtkWidget *dialog;           // Pointer on the dialog where the entry-
                                    // widget is shown
extern GtkWidget *label;            // Pointer on the timer-label
extern GtkWidget *window;           // Pointer on the game-window

extern GtkContainer *container;     // Pointer on the container where all
                                    // graphical items are stored

extern Field grid[9][9];            // Sudoku grid

extern char name[256];              // Sudoku file name

extern int gameTime;                // Timer * 2
extern int numberFields;            // Number of generated values in a new
                                    // sudoku
extern int sec_expired;             // Access the Timer
extern int offset;                  // Get sure timer is running right

extern bool autosave;               // Allow or forbid automated saving
extern bool hints;                  // Allow or forbid automated hints
extern bool windowOpen;             // Store whether the window is open or not

#endif /* GLOBAL_H */