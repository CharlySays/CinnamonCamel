#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gameManagement.h"

/*****  
 * 
 * 
 *                          GLOBAL VARIABLES    
                    further information in global.h                
 
                                                                        *****/

gpointer last;
GtkWidget *lastWidget, *dialog, *entry, *window;
Field grid[9][9];
GtkContainer *container;
bool autosave, hints, windowOpen;
int numberFields, sec_expired, gameTime;

/*****  
 * 
 * 
 *                              Functions  
 
 
                                                                        *****/

/**
 * @FUNCTION getI
 *
 * Returns the i - position of the unit in the grid
 *      
 *      j
 *  i   0   1   2   3   4   5   6   7   8
 *      1   
 *      2   
 *      3   
 *      4   
 *      5   
 *      6   
 *      7   
 *      8   
 * 
 * @PARAMETERS
 * 	int nr - unique id from button in the grid
 *
 */

int getI(int nr);

/**
 * @FUNCTION getJ
 *
 * Returns the j - position of the unit in the grid
 *      
 *      j
 *  i   0   1   2   3   4   5   6   7   8
 *      1   
 *      2   
 *      3   
 *      4   
 *      5   
 *      6   
 *      7   
 *      8   
 * 
 * @PARAMETERS
 * 	int nr - unique id from button in the grid
 *
 */

int getJ(int nr);

/**
 * @FUNCTION locked
 *
 * Returns whether the button is locked or not
 *      
 * @PARAMETERS
 * 	int nr - unique id from button in the grid
 *
 */

bool locked(int nr);

/**
 * @FUNCTION checkFilled
 *
 * Returns whether all units in the grid are filled or not
 *
 */

bool checkFilled();

/**
 * @FUNCTION checkValid
 *
 * Returns whether the sudoku is a valid sudoku or not
 *      
 */

bool checkValid();

/**
 * @FUNCTION newGrid
 *
 * Create a new Sudoku
 *      
 */

void newGrid();

/**
 * @FUNCTION setKeyNumber
 *
 * Set the values in sudoku units with keys
 *      
 * @PARAMETERS
 * 	guint keyal - unique key identifier
 *
 */

void setKeyNumber(guint keyval);



/***** 
 * 
 * 
 *                       Callback Functions  
 
 
 
 
                                                                        *****/
/**
 * @FUNCTION callback
 *
 * This is a callback for the clicked event. If a field is clicked this
 * callback function sets the new .css style and marks which field was clicked
 *      
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer nr         - Unique identifier of the caused element 
 *                            in the sudoku grid
 *
 */

void callback( GtkWidget *widget, gpointer nr);

/**
 * @FUNCTION on_key_press
 *
 * This is a callback for the key_press event. If a key is pressed this
 * callback function sets the new .css style and marks the current unit
 *      
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      GdkEventKey *event  - Key which caused this callback with additional
 *                            information
 *      gpointer nr         - Unique identifier of the caused element 
 *                            in the sudoku grid
 *
 */

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);

/**
 * @FUNCTION on_press
 *
 * This is a callback for the key_press event. If the enter-key is pressed this
 * callback function closes the filename dialog and stores the filename in the
 * global variable "name". The sudoku will be generated after the filename is 
 * stored
 *      
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      GdkEventKey *event  - Key which caused this callback with additional
 *                            information
 *      gpointer user_data  - The user_data is a pointer on the overlaying 
 *                            GtkWidget
 *
 */

void on_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);

/**
 * @FUNCTION quit
 *
 * This is a callback which destroys the app
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void quit( GtkWidget *widget, gpointer user_data);

/**
 * @FUNCTION createNewGame
 *
 * This is a callback which creates a new sudoku game
 *       
 * @PARAMETERS
 * 	GtkWidget *widget       - Pointer on the element which causes 
 *                                this callback
 *      gpointer numOfFields    - Number of values in the sudoku
 */

void createNewGame( GtkWidget *widget, gpointer numOfFields);

/**
 * @FUNCTION loadGame
 *
 * This is a callback which loads a existing sudoku
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void loadGame( GtkWidget *widget, gpointer user_data);

/**
 * @FUNCTION saveGame
 *
 * This is a callback which saves the current sudoku
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void saveGame( GtkWidget *widget, gpointer user_data);

/**
 * @FUNCTION resetGame
 *
 * This is a callback which resets the current sudoku
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void resetGame(GtkWidget *widget, gpointer user_data);

/**
 * @FUNCTION toggleSave
 *
 * This is a callback which sets a global variable to allow or forbid automated
 * saving
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void toggleSave( GtkWidget *widget, gpointer user_data);

/**
 * @FUNCTION toggleHints
 *
 * This is a callback which sets a global variable to allow or forbid hints
 *       
 * @PARAMETERS
 * 	GtkWidget *widget   - Pointer on the element which causes this callback
 *      gpointer user_data  - This information will be ignored - always type in
 *                            NULL
 */

void toggleHints( GtkWidget *widget, gpointer user_data);

#endif /* CONTROLLER_H */