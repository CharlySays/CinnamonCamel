#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

#include "generator.h"
#include "global.h"

/*****  
 * 
 * 
 *                          GLOBAL VARIABLES    
                
 
                                                                        *****/
gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];
int gameTime;

/*****  
 * 
 * 
 *                              Functions  
 
 
                                                                        *****/
/**
 * @FUNCTION gridToFile
 *
 * Save the current sudoku in the directory .gamefiles with the given file name 
 *      
 * @PARAMETERS
 * 	char* fileName   - Under this name the sudoku will be stored 
 *
 */

void gridToFile(char* fileName);

/**
 * @FUNCTION readGridWithFile
 *
 * Open a sudoku out of a file and returns true if all works fine
 *      
 * @PARAMETERS
 * 	char* fileName      - Under this name the sudoku is stored 
 *      int numberOfFields  - Number of values in the sudoku
 *
 */

bool readGridWithFile(char *fileName, int numberOfFields);

#endif /* GAMEMANAGEMENT_H */