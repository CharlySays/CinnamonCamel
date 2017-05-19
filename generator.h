#ifndef GENERATOR_H
#define GENERATOR_H

#include "global.h"

/*****  
 * 
 * 
 *                          GLOBAL VARIABLES    
                
 
                                                                        *****/
gpointer last;
GtkWidget *lastWidget;
Field grid[9][9];

/*****  
 * 
 * 
 *                              Functions  
 
 
                                                                        *****/

/**
 * @FUNCTION solvePuzzle
 *
 * Recursively test every non pre-filled field in given sudoku for every possible number (1-9)
 * until a valid solution for every "empty" Field (filled with 0) is found.
 * If a previously set Number proves the further solving of the puzzle impossible, the function returns 0
 * and the upper level function call tries the next possibility.
 *
 * @PARAMETERS
 * 	int row - row address where the function should start to try out numbers
 * 	int col - column address where the function should start to try out numbers
 *
 */

int solvePuzzle(int row, int column);

/**
 * @FUNCTION printPuzzle
 *
 * !For developing purposes only!
 * Prints a two dimensional array to the command line
 */

void printPuzzle();

/**
 * @FUNCTION removeNNumbers
 *
 * Removes N numbers from a sudoku
 *
 * @PARAMETERS
 * 	int numbers - integer value of the amount of numbers, that are to be removed
 *
 */

void removeNNumbers( int numbers);

/**
 * @FUNCTION prepareForGui
 *
 * Prepare the sudoku structure for the Graphical User Interface. For Example
 * all zero values will be shown as an empty unit. 
 *
 */

void prepareForGUI();

/**
 * @FUNCTION generateGrid
 *
 * Generate a new sudoku with an given amount of numbers 
 *      
 * @PARAMETERS
 * 	int numFields   - Given amount of numbers
 *
 */

void generateGrid(int numFields);

/**
 * @FUNCTION isValid
 *
 * checks the correctness of the Game from the point of view of one single number (int number)
 *
 * @PARAMETERS
 * 	int row, int col - Two Integer Values describing the Position in the Sudoku-Game/Array to be tested for Conformity
 * 						with the rules of Sudoku
 * 	int number 	- The Number to be tested
 *
 */

int isValid(int row, int column, int number);

#endif /* GENERATOR_H */