#ifndef VIEW_H
#define VIEW_H

#include "controller.h"
#include "global.h"

/*****  
 * 
 * 
 *                          GLOBAL VARIABLES    
                
 
                                                                        *****/
gpointer last;
GtkWidget *lastWidget, *dialog, *entry, *label, *window;
Field grid[9][9];
char name[256];
int gameTime;
GtkContainer *container;
bool autosave, hints, windowOpen;

/*****  
 * 
 * 
 *                              Functions  
 
 
                                                                        *****/
/**
 * @FUNCTION myCss
 *
 * This function allows to style the GTK3+ Application with .css
 *
 */

void myCss(void);

/**
 * @FUNCTION setStyleClicked
 *
 * Set the new .css style
 *
 * @PARAMETERS
 * 	int x           - i - position of the button
 *      int y           - j - position of the button
 *      bool clicked    - Information whether the button is clicked or not
 *
 */

void setStyleClicked(int x, int y, bool clicked);

/**
 * @FUNCTION setCurrentNumber
 *
 * Sets the current number in the last clicked/pressed sudoku unit
 *
 * @PARAMETERS
 * 	GtkWidget *widget   - Necessary for calling like a callback
 *      int nr              - To be set number
 * 
 */

void setCurrentNumber(GtkWidget *widget, int nr);

/**
 * @FUNCTION fill_grid_with_buttons
 *
 *  This is after the Field struct the second elementary function in this
 *  sudoku project. This function creates all buttons and hense the data model
 *  of the whole sudoku. 
 *
 * @PARAMETERS
 * 	GtkWidet *gtkGrid   -   Grid where the button are shown and stored in
 *
 */

void fill_grid_with_buttons(GtkWidget *gtkGrid);

/**
 * @FUNCTION createDialog
 *
 * Create a dialog to read-in the file name of the to be opened or to be 
 * generated sudoku
 *
 * @PARAMETERS
 * 	GtkWidget *parent   -   Overlaying widget
 *
 */
void createDialog(GtkWidget *parent);

/**
 * @FUNCTION createMenu
 *
 * Create a menu bar with different functionalities like save or load or create
 * a new sudoku
 *
 */

GtkWidget* createMenu(void);

/**
 * @FUNCTION create_pixbuf
 *
 * Store icon data to show this icon
 *
 * @PARAMETERS
 * 	const gchar *filename   -   File name of the icon
 *
 */

GdkPixbuf* create_pixbuf(const gchar * filename);

/**
 * @FUNCTION setCorresponding
 *
 * Show hints by coloring all same values in the sudoku
 *
 * @PARAMETERS
 * 	int x   - i - position of the button
 *      int y   - j - position of the button
 *      int val - value of the button / sudoku unit
 *
 */

void setCorresponding(int x, int y, int val);

#endif /* VIEW_H */