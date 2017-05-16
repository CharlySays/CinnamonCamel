/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   global.h
 * Author: nils
 *
 * Created on May 9, 2017, 5:05 PM
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include "grid.h"
#include <gtk/gtk.h>

extern gpointer last;
extern GtkWidget *lastWidget, *entry, *dialog, *label;
extern Field grid[9][9];
extern char name[256];
extern int gameTime, numberFields;
extern GtkContainer *container;
extern bool autosave, hints;

#endif /* GLOBAL_H */

