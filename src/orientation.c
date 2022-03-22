#include <stdio.h>

/**
 * @brief Initializing an array at 0
 * 
 * @param array A piece array
 */
void initZero(int array[7][7]){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            array[i][j] = 0;
        }
    }
}

/**
 * @brief Get the max value on the j side
 * 
 * @param array A piece array
 * @return int  the index of the max
 */
int jmax(int array[7][7]){
    int max = 0;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            if (array[i][j]!=0 && j>max){
                max = j;
            }
        }
    }
    return(max);
}

/**
 * @brief Function to miror an array
 * 
 * @param origin    The actuel state of the piece 
 * @param new       The array that will be the output
 */
void miror(int origin[7][7],int new[7][7]){
    initZero(new);
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            new[i][j] = origin[i][jmax(origin)-j];
        }
    }
}

/**
 * @brief Copy a piece array into another
 * 
 * @param origin    The input
 * @param new       The output
 */
void copy(int origin[7][7],int new[7][7]){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            new[i][j] = origin[i][j];
        }
    }
}

void rotateRigth(int origin[7][7],int new[7][7]){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            new[i][j] = origin[jmax(origin)-j][i];
        }
    }
}

void rotateLeft(int origin[7][7],int new[7][7]){
    for (int rot = 0; rot < 3 ; rot++){
        rotateRigth(origin,new);
        copy(new,origin);
    }
}