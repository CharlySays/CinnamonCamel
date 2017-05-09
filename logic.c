#include "logic.h"

bool culCheck(Field grid[][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                if(grid[j][i].value==grid[k][i].value && j!=k && grid[j][i].value != 0 && grid[k][i].value != 0){
                    //printf("Spaltenfehler bei Positionen: %d:%d   %d:%d",j,i,j,k);
                    return false;
                    }
                }
            }
        }
    return true;
}

bool rowCheck(Field grid[][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                if(grid[i][j].value==grid[i][k].value && grid[i][j].value != 0 && grid[i][k].value != 0 && j != k){
                    //printf("Reihenfehler bei Positionen: %d:%d   %d:%d",i,j,k,j);
                    return false;
                }

            }
        }
    }
    return true;
}

bool culCheckField(Field grid[][9],int x, int y){
    if(grid[y][x].value==0){
        return true;
    }
    for(int k=0;k<9;k++){
        if((grid[y][x].value==grid[k][x].value && y!=k)){
            return false;
        }
    }
    return true;
}

bool rowCheckField(Field grid[][9], int x, int y){
    if(grid[y][x].value==0){
        return true;
    }
    for(int k=0;k<9;k++){
        if((grid[y][x].value==grid[y][k].value && x!=k)){
            return false;
        }
    }
    return true;
}

bool squareCheckField(Field grid[][9],int x, int y){
    if(grid[y][x].value==0){
        return true;
    }

    int topX = x;
    int topY = y;
    while(!(topX%3==0) || !(topY%3==0)){
        if(!(topX%3==0)){
            topX--;
        }
        if(!(topY%3==0)){
            topY--;
        }
    }

    for(int i=topY;i<topY+3;i++){
        for(int j=topX;j<topX+3;j++){
            if((i!=y || j!=x) && grid[i][j].value==grid[y][x].value){
                return false;
            }
        }
    }

    return true;
}

bool winCondition(Field grid[][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(grid[i][j].value==0){
                return false;
            }
            if(!rowCheckField(grid,i,j) || !culCheckField(grid,i,j) || !squareCheckField(grid,i,j)){
                return false;
            }
        }
    }
    return true;
}


