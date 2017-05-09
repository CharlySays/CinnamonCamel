#include "generator.h"

void generateGrid(int numFields){
    
    srand(time(NULL));
        
    int iteratorOne, iteratorTwo;
    /* Initialize everything with 0 */
    for (iteratorOne = 0; iteratorOne < 9; iteratorOne++) {
	for (iteratorTwo = 0; iteratorTwo < 9; iteratorTwo++) {
		grid[iteratorOne][iteratorTwo].value = 0;
        }
    }
    
    solvePuzzle(0,0);
    removeNNumbers(81-numFields);
    prepareForGUI();
}


/**
 * @FUNCTION removeNNumbers
 *
 * Removes N numbers from a sudoku
 *
 * @PARAMETERS
 * 	int (*puzzle)[9][9] - Pointer to an array containing the current state of the Sudoku
 * 	int numbers - integer value of the amount of numbers, that are to be removed
 *
 */

void prepareForGUI(){
    int i,k;
    for(i=0;i<9;i++){
        for(k=0;k<9;k++){
            if(grid[i][k].value){
                grid[i][k].fixed = true;
                strcpy(grid[i][k].show,itoa(grid[i][k].value,grid[i][k].show,10));
            }else{
                 grid[i][k].fixed = false;
                strcpy(grid[i][k].show," ");
            }
        }
    }
}

void removeNNumbers(int numbers) {

	while (numbers) {
		int row, column;
		row = (rand() % 9);
		column = (rand() % 9);
		if (grid[row][column].value) {
			grid[row][column].value = 0;
			numbers--;
		}
	}

}

/**
 * @FUNCTION printPuzzle
 *
 * !For developing purposes only!
 * Prints a two dimensional array to the command line
 *
 * @PARAMETERS
 * 	int (*puzzle)[9][9] - Pointer to an array containing the current state of the Sudoku
 *
 */
void printPuzzle() {
	int row, column;
	for (row = 0; row < 9; row++) {
		for (column = 0; column < 9; column++) {
			printf(" %d ", grid[row][column].value);
		}
		printf("\n");
	}
	printf("\n __________________________\n");
}

/**
 * @FUNCTION isValid
 *
 * checks the correctness of the Game from the point of view of one single number (int number)
 *
 * @PARAMETERS
 * 	int (*puzzle)[9][9] - Pointer to an array containing the current state of the Sudoku
 * 	int row, int col - Two Integer Values describing the Position in the Sudoku-Game/Array to be tested for Conformity
 * 						with the rules of Sudoku
 * 	int number 	- The Number to be tested
 *
 */

int isValid(int row, int column, int number) {
	int iterator = 0;
	int sectorRow = 3 * (row / 3);
	int sectorColumn = 3 * (column / 3);
	int row1 = (row + 2) % 3;
	int row2 = (row + 4) % 3;
	int column1 = (column + 2) % 3;
	int column2 = (column + 4) % 3;

	/* Check for the value in the given row and column */
	for (iterator = 0; iterator < 9; iterator++) {
		if (grid[iterator][column].value == number)
			return 0;
		if (grid[row][iterator].value == number)
			return 0;
	}

	/*
	 *  Check the remaining four spaces in this sector
	 * 	Example:
	 *
	 * 		| * | x | * |
	 * 		| x | x | x |
	 * 		| * | x | * |
	 *
	 * Since we checked the corresponding row and column above (Boxes with the 'x'),
	 * we now have to check the 4 remaining	Fields containing '*'
	 * inside the 3x3 cube our verifiable Field belongs to
	 *
	 */
	if (grid[row1 + sectorRow][column1 + sectorColumn].value == number)
		return 0;
	if (grid[row2 + sectorRow][column1 + sectorColumn].value == number)
		return 0;
	if (grid[row1 + sectorRow][column2 + sectorColumn].value == number)
		return 0;
	if (grid[row2 + sectorRow][column2 + sectorColumn].value == number)
		return 0;
	return 1;
}
/**
 * @FUNCTION solvePuzzle
 *
 * Recursively test every non pre-filled field in given sudoku for every possible number (1-9)
 * until a valid solution for every "empty" Field (filled with 0) is found.
 * If a previously set Number proves the further solving of the puzzle impossible, the function returns 0
 * and the upper level function call tries the next possibility.
 *
 * @ PARAMETERS
 * 	int (*puzzle)[9][9] - Pointer to an array containing the current state of the Sudoku
 * 	int row - row address where the function should start to try out numbers
 * 	int col - column address where the function should start to try out numbers
 *
 */
int solvePuzzle(int row, int column) {

	/* First we check if we are already done (we're lazy shits I tell ya)*/
	if (row < 9 && column < 9) {
		/* if there is a pregiven Number move to the next field */
		if (grid[row][column].value != 0) {
			/* next recursive call of the solver */
			if ((column + 1) < 9) {
				return solvePuzzle(row, column + 1);
			} else {
				return solvePuzzle(row + 1, 0);
			}
		} else {
			/* Fill an array with the numbers 1-9 but in random order */
			int iterator, randomNumber;
			int *pointer;
			int randomizedNumbers[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			pointer = randomizedNumbers;
			iterator = 0;
			while (iterator < 9) {
				randomNumber = rand() % 9 + 1;
				if (!isValueInArray(randomNumber, pointer, 9)) {
					randomizedNumbers[iterator] = randomNumber;
					iterator++;
				}
			}
			/*iterate over the array for a possible valid number */
			for (iterator = 0; iterator < 9; ++iterator) {
				if (isValid(row, column, randomizedNumbers[iterator])) {
					/* if a valid number is found write it to the array and start the next recursive call */
					grid[row][column].value = randomizedNumbers[iterator];
					if ((column + 1) < 9) {
						if (solvePuzzle(row, column + 1)) {
							return 1;
						} else {
							/* if recursive call returns 0 reset the number to 0 again and try the next possibility */
							grid[row][column].value = 0;
                                                        
						}
					} else {
						if (solvePuzzle(row + 1, 0)) {
							return 1;
						} else {
							/* if recursive call returns 0 reset the number to 0 again and try the next possibility */
							grid[row][column].value = 0;
						}
					}
				}
			}
		}
		return 0;
	} else {
		return 1;
	}
}
