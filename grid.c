#include "grid.h"

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
    grid[Y-1][X-1].value = value;
    strcpy(grid[Y-1][X-1].show,itoa(value,grid[Y-1][X-1].show,10));
    return true;
}


