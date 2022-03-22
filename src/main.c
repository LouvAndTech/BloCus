/**
 * @file main.c
 * @author Matthieu Evain && Elouan Lérissel 
 * @brief Blocus game 
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Libraries 
#include<stdio.h>

//Other files
#include "plateau.c"

//constant
#define SIZE_PLAT 22
#define NUMBER_PIECES 21

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
        p.remaingin[i]=i;
    }
    return p;
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
    //Initialise a list to store each player continue or loos state in the game 
    Player playerL[4] = {initPlayer(),initPlayer(),initPlayer(),initPlayer()};
    //start with the player 1:
    int player = 1;
    //While the game is not win yet
    while (game_running){
        if (playerL[player].up){
            int state = 0;
            while (state != 5){
                switch (state)
                {
                //Tell the player it's they turn
                case 0:
                    printf("C'est au joueur %d de jouer !",player);
                    getchar();
                    state = 1;
                    break;
                //piece selection 
                case 1:
                    printf("Choisi une piece a jouer");
                    //WIP :
                        //selection = good ==> state = 2
                    break;

                //select an orientation 
                case 2:
                    printf("Choisi un endroit ou mettre la pièce.");
                    //WIP 
                        //validate orientation ==> state = 3
                        // want to change piece ==> state 1
                    break;

                //Select a place to place the piece 
                case 3:
                    printf("Choisi un endroit ou mettre la pièce.");
                    //WIP 
                        //place = good ==> state = 4
                        // want to change orientation ==> state 2
                    break;

                //updateing the piece in his inventory 
                case 4:
                    printf("WIP");
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