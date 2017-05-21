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
    
    int time;
    
    offset == 2 ? gameTime : gameTime*2;
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
       myFile = fopen(fileName, "wb");
       generateGrid(numberOfFields);
       gridToFile(fileName);
       fclose(myFile);
       myFile = fopen(fileName, "r+");
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
            }else{
                grid[i][j].fixed = false;
            }
        }
    }
    
    char time[10] = "\0";
    while(fgets(temp,2,myFile)){
        strcat(time,temp);
    }
    
    gameTime = atoi(time);
    sec_expired = gameTime;
    
    char timer[50] = "Time elapsed: ";
    char gameTimeChar[20];
    strcat(timer, itoa(gameTime/(60*offset), gameTimeChar, 10));
    if((gameTime/offset)%60 < 10) strcat(timer, ":0");
    else strcat(timer, ":");
    strcat(timer, itoa((gameTime/offset)%60, gameTimeChar, 10));
    
    if(label != NULL) gtk_label_set_text(GTK_LABEL(label), timer);
    g_print("%i", gameTime);
    return true;
}