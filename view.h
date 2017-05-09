/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   view.h
 * Author: nils
 *
 * Created on May 9, 2017, 4:21 PM
 */

#ifndef VIEW_H
#define VIEW_H

#include "stdbool.h"
#include "grid.h"
#include "controller.h"

gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];
char name[256];

void myCss(void);
void setStyleClicked(int x, int y, bool clicked);
void setCurrentNumber(GtkWidget *widget, int nr);
void fill_grid_with_buttons(GtkWidget *gtkGrid);

#endif /* VIEW_H */

