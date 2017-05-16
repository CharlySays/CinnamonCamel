#include "gameManagement.h"

void gridToFile(char* fileName){
    char output[1024] = "\0";
    char temp[1024] = "\0";
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            itoa(grid[i][j].value,temp,10);
            strcat(output,temp);
        }
    }
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(grid[i][j].fixed){
                strcat(output,"1");
            }else{
                strcat(output,"0");
            }
        }
    }
    
    strcat(output,itoa(gameTime,temp,10));
    
    FILE *myFile = fopen(fileName,"w");
    fputs(output,myFile);
    fclose(myFile);
}

bool readGridWithFile(char *fileName, int numberOfFields){
    //read file into array
    
    FILE *myFile = fopen(fileName, "r+");
    if(myFile == NULL) //if file does not exist, create it
    {
       myFile = fopen(name, "wb");
       generateGrid(numberOfFields);
       gridToFile(name);
       fclose(myFile);
       myFile = fopen(name, "r+");
    }

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(!(fgets(grid[i][j].show,2,myFile))){
                return false;
            }
            grid[i][j].value = atoi(grid[i][j].show);
        }
    }
    
    char temp[10] = "\0";
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(!(fgets(temp,2,myFile))){
                return false;
            }
            if(atoi(temp) != 0){
                grid[i][j].fixed = true;
                grid[i][j].correct = true;
            }else{
                grid[i][j].fixed = false;
                grid[i][j].correct = false;
            }
        }
    }
    
    char time[10] = "\0";
    while(fgets(temp,2,myFile)){
        strcat(time,temp);
    }
    
    gameTime = atoi(time);
    
    return true;
}