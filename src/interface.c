#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Retourne un cadre de x par y
 * 
 * @param x max 150
 * @param y max 14
 */
void interface(int x, int y){
    system("clear");
    //Print le haut du cadre
    printf("╔");
    for(int i=0; i<x; i++){
        printf("═");
    }
    printf("╗\n");
    //Print le millieu du cadre
    for(int j=0; j<y; j++){
        printf("║");
        for(int k=0; k<x; k++){
            printf(" ");
        }
        printf("║\n");
    }
    //Print le bas du cadre
    printf("╚");
    for(int i=0; i<x; i++){
        printf("═");
    }
    printf("╝\n");
}
void green() {
  printf("\033[0;32m");
}

void red(){
  printf("\033[0;31m");
}

void yellow(){
  printf("\033[0;33m");
}

void blue(){
  printf("\033[0;34m");
}

void reset () {
  printf("\033[0m");
}

/*MAIN DE TEST
int main(){
    interface(150,14);
    return(0);
}*/