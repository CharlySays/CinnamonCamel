    #include "gameManagement.h"

void gridToFile(Field grid[][9], char* fileName){
    char output[255] = "\0";
    char temp[255];
    strcpy(temp,"\0");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            itoa(grid[i][j].value,temp,10);
            strcat(output,temp);
        }
    }

    FILE *myFile = fopen(fileName,"w");
    fputs(output,myFile);
    fclose(myFile);
}

bool readGridWithFile(Field grid[][9], FILE *myFile){
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

    return true;
}
