#include <stdio.h>

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

/*MAIN DE TEST
int main(){
    interface(150,14);
    return(0);
}*/