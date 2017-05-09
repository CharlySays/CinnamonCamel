#include "grid.h"

bool readGrid(Field grid[][9]){
    FILE *myFile;
    myFile = fopen("somenumbers.txt", "r");

    //read file into array

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(!(fgets(grid[i][j].show,2,myFile))){
                return false;
            }
            grid[i][j].value = atoi(grid[i][j].show);
            if(atoi(grid[i][j].show) != 0){
                grid[i][j].fixed = true;
                grid[i][j].correct = true;
            }else{
                grid[i][j].fixed = false;
                grid[i][j].correct = false;
            }
        }
    }

    fclose(myFile);
    return true;
}


void render(Field grid[][9] ,int X, int Y){
    char output[100];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if((i==Y-1 && j==X-1) && (X!=0 && Y!=0)){
                strcat(output,"|");
                strcat(output,grid[i][j].show);
                strcat(output,"|");
            }else{
                strcat(output," ");
                strcat(output,grid[i][j].show);
                strcat(output," ");
            }
        }
        printf("%s\n",output);
        memset(output, 0, sizeof(output));
    }
}

void renderInt(Field grid[][9] ,int X, int Y){
    char output[100];
    char str[10];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if((i==Y-1 && j==X-1) && (X!=0 && Y!=0)){
                if(grid[i][j].value == 0){
                    strcat(output,"|_|");
                }else{
                    strcat(output,"|");
                    strcat(output,itoa(grid[i][j].value,str,10));
                    strcat(output,"|");
                }
            }else{
                if(grid[i][j].value == 0){
                    strcat(output,"   ");
                }else{
                    strcat(output," ");
                    strcat(output,itoa(grid[i][j].value,str,10));
                    strcat(output," ");
                }
            }
            if(j==2||j==5){
                strcat(output,"|");
            }
            if(j==8){
                if(j==8 && (i == 2 || i == 5)){
                    strcat(output,"\n_________|_________|_________");
                }
                    strcat(output,"\n         |         |         \n");
            }
        }
        printf("%s",output);
        memset(output, 0, sizeof(output));
    }
}

bool insertValue(Field grid[][9], int value, int X, int Y){
    if(isfixed(grid,X,Y) || !validNum(value)){
        return false;
    }

    grid[Y-1][X-1].value = value;
    strcpy(grid[Y-1][X-1].show,itoa(value,grid[Y-1][X-1].show,10));
    return true;
}

bool isfixed(Field grid[][9], int X, int Y){
    return grid[Y-1][X-1].fixed;
}


