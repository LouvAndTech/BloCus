#include <stdio.h>
#include <stdlib.h>

//constant
#define SIZE_PLAT 22
#define NUMBER_PIECES 21

//Joueur 1
void red(){
  printf("\033[0;31m");
}
//Joueur 2
void green() {
  printf("\033[0;32m");
}
//Joueur 3
void yellow(){
  printf("\033[0;33m");
}
//Joueur 4
void blue(){
  printf("\033[0;34m");
}
//reset all the color
void reset () {
  printf("\033[0m");
}

/**
 * @brief  function to print a piece
 * 
 * @param piece //the piece to print
 */
void printPiece(int piece[7][7]){
    system("clear");
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            //if the piece dont have a start in the corner, we put a red chip
            if(piece[1][1]!=1 && (i==1&&j==1)){
                red();
                printf("■");
                reset();
                printf(" ");
            }
            //else it color the start of the piece in red
            else{
                if(i==1&&j==1){
                    red();
                }
                if(piece[i][j]==1){
                    printf("██");
                }
                else{
                    printf("  ");
                }
                reset();
            }

        }
        printf("\n");
    }
    getchar();
}

void printAllPieces(){
    system("clear");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  0   1   2   3     4     5   6     7     8       9     10    11    12  13    14      15    16      17      18      19        20    ║\n");
    printf("║  ██  ██  ██  ██    ██    ██  ██    ████  ████    ██    ██    ██    ██  ████  ██      ██    ██      ████    ██      ██        ██    ║\n");
    printf("║      ██  ██  ████  ██    ██  ████  ████    ████  ██    ██    ██  ████    ██  ████    ██    ██        ████  ██████  ██████  ██████  ║\n");
    printf("║          ██        ██  ████  ██                  ██    ██  ████  ████  ████  ██    ██████  ██████      ██      ██    ██      ██    ║\n");
    printf("║                    ██                            ██  ████  ██                ██                                                    ║\n");
    printf("║                                                  ██                                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Continue...\n");
    getchar();
    getchar();
    system("clear");
}

/**
 * @brief Print the board
 * 
 * @param tab the board to print
 */
void printTheBoard(int tab[SIZE_PLAT][SIZE_PLAT],int colonne){
    // printf("\n>>> %d\n",colonne);
    printf("\n     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21\n# --------------------------------------------------------------------\n");
    for (int i = 0; i < SIZE_PLAT; i++){
        printf(i>9?"%d |":" %d |",i);
        for (int j = 0; j < SIZE_PLAT; j++){

            //if colonne !=0 and we are in the same column and we are not at the beginning and at the end of the tab
            if((colonne!=0 && j==colonne) && (i!=0 && i!=21)){
                red();
                printf("|");
                reset();
            }
            if(tab[i][j]==5){
                if(i==0 || i==21){
                    printf("═══");
                }
                else{
                    printf(" ║ ");
                }
            }
            //Joueur 1
            else if (tab[i][j]==1 && (i!=0&&j!=0)){
                red();
                printf("███");
                reset();
            }
            //Joueur 2
            else if (tab[i][j]==2 && (i!=0&&j!=0)){
                green();
                printf("███");
                reset();
            }
            //Joueur 3
            else if (tab[i][j]==3 && (i!=0&&j!=0)){
                yellow();
                printf("███");
                reset();
            }
            //Joueur 4
            else if (tab[i][j]==4 && (i!=0&&j!=21)){
                blue();
                printf("███");
                reset();
            }
            else if(tab[i][j]==0){
                printf("   ");
            }
            else{
                printf(" %d ",tab[i][j]);
            }
        }
        printf("\n");
    }
}