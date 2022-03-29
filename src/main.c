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

//Other files
#include "plateau.c"
#include "piece.c"
#include "orientation.c"
#include "boardXpiece.h"

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
        int remaingin[NUMBER_PIECES];
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
            p.remaingin[i]=1;
        }
        return p;
    }
//END CLASS

void printPiece(int piece[7][7]){
    printf("\n");
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            printf("%d ",piece[i][j]);
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
    for (int i = 0; i < SIZE_PLAT; i++){
        for (int j = 0; j < SIZE_PLAT; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
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
    //Printing the board
    for(int i=0; i<SIZE_PLAT; i++){
        for(int j=0; j<SIZE_PLAT; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }

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
            int pieceActuel[7][7]; //Store the piece in it's actual state
            while (state != 5){
                switch (state)
                {
                //Tell the player it's they turn
                case 0:
                    printf("C'est au joueur %d de jouer !",player);
                    getchar();
                    printTheBoard(tab);
                    state = 1;
                    break;

                //piece selection 
                case 1:
                    printf("Selection de la piece\n");
                    //Store the choosen piece
                    int pieceChoose;
                    do{
                        printf("Choisi une piece a jouer (0-20): ");
                        //get the value
                        scanf("%d",&pieceChoose);
                        //Check if the player still got the piece in inventory
                    }while (playerL[player].remaingin[pieceChoose]==0 || pieceChoose>20 || pieceChoose<0);
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
                                    printTheBoard(tab);
                                    printf("\nEntrer une colonne(0 pour revenir): \n-> ");
                                    scanf("%d",&pos[0]);
                                    printf("\n");
                                }while(choice<1 || choice>20);
                                if(choice){
                                    localState = 1;
                                }else{
                                    state = 2;
                                }
                                break;

                            case 1: //Enter y
                                do{
                                    printTheBoard(tab);
                                    printf("\nEntrer une ligne (0 pour revenir): \n-> ");
                                    scanf("%d",&pos[1]);
                                    printf("\n");
                                }while(choice<0 || choice>20);
                                if(choice){
                                    localState = 2;
                                }else{
                                    localState = 0;
                                }
                                break;

                            case 2:
                                //Check if the place is free
                                if(checkPos(tab,pieceActuel,pos,player)){
                                    placePiece(tab,pieceActuel,pos,player);
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

                //updateing the piece in his inventory 
                case 4:
                    printf("WIP");
                    /*
                    //Check if the player win
                    if(checkWin(tab,playerL[player].score)){
                        printf("\nLe joueur %d a gagné !\n",player);
                        game_running = 0;
                    }*/
                    //WIP 
                        //removing the choosen piece from the remaining ones 
                        //if the remaining piece = 1 check if it's the square, if it is add the bonus 
                    break;
                }
            }
        }
        //Check for each player if they are able to play 
        //----WIP----
        //Switch to the next player
        player = (player==4)? 1 : player+1;
    }
    
    return 0;
}