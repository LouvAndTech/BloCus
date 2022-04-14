/**
 * @file main.c
 * @author Matthieu Evain && Elouan Lérissel 
 * @brief Blocus game 
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (C) 2007 Free Software Foundation
 * 
 */

//Libraries 
#include<stdio.h>
#include <stdlib.h>

//Other files
#include "plateau.c"
#include "piece.c"
#include "orientation.c"
#include "boardXpiece.c"
#include "interface.c"

//constant
#define SIZE_PLAT 22
#define NUMBER_PIECES 21


//CLASS PLAYER
    /**
     * @brief Struct to keep the diffrents info about a player
     * 
     * @param score to keep the score he win
     * @param remaining to keep the track of the piece remaining in is inventory
     * @param bonus to remember if he got the bonus point
     * @param up to know if he still up or he 
     */
    typedef struct {
        int score;
        int inventory[NUMBER_PIECES];
        int bonus;
        int up;

    }Player;
    
    //CONSTRUCTOR
    /**
     * @brief init a player
     * 
     * @return Player initialized
     */
    Player initPlayer(){
        Player p;
        p.score = 0;
        p.bonus=0;
        p.up=1;
        for (int i = 0; i < NUMBER_PIECES; i++){
            p.inventory[i]=1;
        }
        return p;
    }
//END CLASS

/**
 * @brief  function to print a piece
 * 
 * @param piece //the piece to print
 */
void printPiece(int piece[7][7]){
    printf("\n");
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            printf("%d ",piece[i][j]);


            // if(i==1&&j==1){
            //     red();
            // }
            // if(piece[i][j]==1){
            //     printf("██-");
            // }
            // else{
            //     printf("XXX");
            // }
            // reset();
        }
        printf("\n");
    }
    getchar();
}

/**
 * @brief Print the board
 * 
 * @param tab the board to print
 */
void printTheBoard(int tab[SIZE_PLAT][SIZE_PLAT]){
    printf("\n     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21\n# --------------------------------------------------------------------\n");
    for (int i = 0; i < SIZE_PLAT; i++){
        printf(i>9?"%d |":" %d |",i);
        for (int j = 0; j < SIZE_PLAT; j++){
            if(tab[i][j]==5){
                if(i==0 || i==21){
                    printf("═══");
                }
                else{
                    printf(" ║ ");
                }
            }
            else if (tab[i][j]==1 && (i!=0&&j!=0)){
                printf("██ ");
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

void fenetre(){

}


/**
 * @brief Main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{   
    //Create the 2D array containing the game-board
    int tab[SIZE_PLAT][SIZE_PLAT];
    //initializing the Array with the a game start
    plateau(tab,SIZE_PLAT);

    //Initializing a variable to store if the game is running or dead
    int game_running = 1;
    //List to store each player state in the game 
    Player playerL[4] = {initPlayer(),initPlayer(),initPlayer(),initPlayer()};
    //start with the player 1:
    int player = 0;
    //While the game is not win yet
    while (game_running){
        //if the player isn't dead yet
        if (playerL[player].up){
            int state = 0; //Store the state in the tour
            int pieceChoose;    //Store the piece choosen by the player
            int pieceActuel[7][7]; //Store the piece in it's actual state
            while (state != 5){
                switch (state)
                {
                //Tell the player it's they turn
                case 0:
                    system("clear");
                    fenetre();
                    printf("C'est au joueur %d de jouer !",player+1);
                    getchar();
                    printTheBoard(tab);
                    state = 1;
                    break;

                //piece selection 
                case 1:
                    printf("\nSelection de la piece\n");
                    do{
                        printf("Choisi une piece a jouer (0-20): ");
                        //get the value
                        scanf("%d",&pieceChoose);
                        if (playerL[player].inventory[pieceChoose]==0){
                            printf("Piece non disponible\n");
                        }
                        //Check if the player still got the piece in inventory
                    }while (playerL[player].inventory[pieceChoose]==0 || pieceChoose>20 || pieceChoose<0);
                    //Get the piece from the database
                    returnPiece(pieceActuel,pieceChoose); 
                    
                    //Print for debug
                    printPiece(pieceActuel);

                    //Switch to the next step
                    state = 2;
                    break;

                //select an orientation 
                case 2:
                    printf("Choisir une orientation.");
                    //Store the choice
                    int choice = 0;
                    int changedPiece[7][7]; //Piece to store the change 
                    initZero(changedPiece);
                    do{
                        switch(choice){
                            //Ask while the answer isn't correct
                            case 0:
                                do{
                                    printf("\n1 - miroir\n2 - droite\n3 - gauche\n4 - valider\n5 - retour\n-> ");
                                    scanf("%d",&choice);
                                    printf("\n");
                                }while(choice<1 || choice>5);
                                break;
                            case 1:
                                //miror pieceActuel and store it into changedPiece
                                miror(pieceActuel,changedPiece);
                                //Them copy changed piece into Pieceactuel
                                copy(changedPiece,pieceActuel);
                                //Print for debug
                                printPiece(pieceActuel);

                                choice = 0;
                                break;
                            case 2:
                                //Rotate right
                                rotateRigth(pieceActuel,changedPiece);
                                //copy to the actual piece
                                copy(changedPiece,pieceActuel);
                                //Print for debug
                                printPiece(pieceActuel);
                                choice = 0;
                                break;
                            case 3:
                                //rotateLeft
                                rotateLeft(pieceActuel,changedPiece);
                                copy(changedPiece,pieceActuel);
                                printPiece(pieceActuel);
                                choice = 0;
                                break;
                            case 4:
                                state = 3;
                                break;
                            case 5:
                                state = 1;
                                break;
                        }                        
                    }while(state == 2);
                    break;

                //Select a place to place the piece 
                case 3:
                    printf("Choisi un endroit ou mettre la pièce.");
                    int pos[2] = {0,0};
                    int localState = 0;

                    do{
                        switch (localState){
                            case 0: //enter x
                                do{ 
                                    pos[0] = -1;
                                    printTheBoard(tab);
                                    printf("\nEntrer une colonne(0 pour revenir): \n-> ");
                                    scanf("%d",&pos[0]);
                                    printf("\n");
                                }while(pos[0]<0 || pos[0]>20);
                                if(pos[0]){
                                    localState = 1;
                                }else{
                                    state = 2;
                                }
                                break;

                            case 1: //Enter y
                                do{
                                    pos[1] = -1;
                                    printTheBoard(tab);
                                    printf("\nEntrer une ligne (0 pour revenir): \n-> ");
                                    scanf("%d",&pos[1]);
                                    printf("\n");
                                }while(pos[1]<0 || pos[1]>20);
                                if(pos[1]){
                                    localState = 2;
                                }else{
                                    localState = 0;
                                }
                                break;

                            case 2:
                                //Check if the place is free
                                if(checkPos(tab,pieceActuel,pos,player+1)){
                                    placePiece(tab,pieceActuel,pos,player);
                                    printTheBoard(tab); 
                                    //Switch to the next step
                                    state = 4;
                                }else{
                                    printf("\nLa piece ne peut pas être placée ici.\n");
                                    localState = 0;
                                }
                                break;
                        }
                    }while(state ==3);
                    break;

                //update the player inventory and pass to the next
                case 4:
                    //Update the inventory
                    playerL[player].inventory[pieceChoose]=0;

                    //Check if the player is winner
                    if(checkWin(playerL[player].inventory)){
                        printf("\nLe joueur %d a gagné !\n",player);
                        //If they win leave the game 
                        game_running = 0;
                    }else{
                        //check state of each player
                        int playerout = 0;
                        for (int i= 0; i < 4; i++){
                            if (blocked(tab,playerL[i].inventory,player)){
                                playerL[i].up = 0;
                                playerout++;
                            }
                        }
                        if (playerout == 4){
                            printf("\nTous les joueurs sont bloqués !\n");
                            state = 5;
                        }else{
                            //Switch to the next player
                            player = (player+1)%4;
                            if (!playerL[player].up){
                                player = (player+1)%4;
                            }
                            state = 0;
                        }
                    }
                    break;

                //End game
                case 5:
                    printf("\nFin du jeu\n");
                    game_running = 0;
                    break;
                }
            }
        }
    }
    return 0;
}


