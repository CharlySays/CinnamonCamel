#include "util.h"
#include <string.h>

bool validNum(int value){
    if(value<0||value>9){
        return false;
    }
    return true;
}

void coordinateRead(int *value, char C){
    if(!validNum(*value)){
        printf("%c-Koordinate eingeben: ",C);
        readSudokuVal(value);
    }
}

bool readSudokuVal(int *value){
    int result = scanf("%d", value);
    if(!validNum(*value)|| result == 0){
         while (fgetc(stdin) != '\n')
        *value = 10;
         return false;
    }
    return true;
}

char* itoa(int value, char* result, int base) {
        // check that the base if valid
        if (base < 2 || base > 36) { *result = '\0'; return result; }

        char* ptr = result, *ptr1 = result, tmp_char;
        int tmp_value;

        do {
            tmp_value = value;
            value /= base;
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
        } while ( value );

        // Apply negative sign
        if (tmp_value < 0) *ptr++ = '-';
        *ptr-- = '\0';
        while(ptr1 < ptr) {
            tmp_char = *ptr;
            *ptr--= *ptr1;
            *ptr1++ = tmp_char;
        }
        return result;
}


