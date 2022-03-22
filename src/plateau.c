/**
 * @file plateau.c
 * @author Matthieu Evain
 * @brief Plateau
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

//Include header
#include "plateau.h"


/**
 * @brief plateau
 * 
 * @param int* 
 * @param int 
 * @return
 */
int plateau(int tab[22][22], int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if((i==0) || (i==21) || (j==0) || (j==21)){
                tab[i][j]=5;
            }
            else{
                tab[i][j]=0;
            }
        }
    }
    int c=1;
    for(int k=0; k<22; k+=21){
        for(int l=0; l<22; l+=21){
            tab[k][l]=c;
            c++;
        }
    }
    return 0;
}