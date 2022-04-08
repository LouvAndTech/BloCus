#include <stdio.h>
#include <stdlib.h>

#define SIZE_PLAT 22

typedef struct{
    int player_turn; //Wich player is suposed to play next
    char *piece_restante; //Each line for a player and each column a piece
    char *board; //The actual state of the board
}Data;

/*===== New Save =====*/
/**
 * @brief Change an array of a board into a string
 *  
 * @param board     2D array with the actual board
 * @param string    A string to contain the board
 */
void stringigyBoard(int board[SIZE_PLAT][SIZE_PLAT],char string[1024]){
    sprintf(string,"");
     for(int i=0; i<SIZE_PLAT; i++){
        for(int j=0; j<SIZE_PLAT; j++){
            sprintf(string,"%s%d",string,board[i][j]);
        }
        sprintf(string,"%s-",string);
    }
    sprintf(string,"%s%c",string,'%');
}

/**
 * @brief Change an array of piece left into a string
 * 
 * @param piece_restante    2D array containing each piece left for each player
 * @param string            A string to contain the output
 */
void stringifyPieces(int piece_restante[4][21],char string[1024]){
    sprintf(string,"");
    for(int i=0; i<4; i++){
        for(int j=0; j<21; j++){
            sprintf(string,"%s%d",string,piece_restante[i][j]);
        }
        sprintf(string,"%s-",string);
    }
    sprintf(string,"%s%c",string,'%');
}

/**
 * @brief Save the game into a file
 * 
 * @param board             2D array with the actual board
 * @param playerturn        int of the player it is the turn
 * @param piece_restante    2D array with the pieces of each player
 */
void newSave(int playerturn, int piece_restante[4][21], int board[22][22]){
    //Format all the datasets
    Data data;
    //The player that's supposed to play
    data.player_turn = playerturn;

    //the state of the board
    char stringedBard[1024];
    stringigyBoard(board,stringedBard);
    data.board = stringedBard;

    //State of the inventories
    char stringedPieces[1024];
    stringifyPieces(piece_restante,stringedPieces);
    data.piece_restante = stringedPieces;

    //Format the string to write
    char finalString[2050];
    sprintf(finalString,"%i|%s|%s$",data.player_turn,data.piece_restante,data.board);

    //Write the data to a file
    FILE *fptr;

    //Open the file
    fptr = fopen("./save.txt","w");

    if(fptr == NULL){
        //Log error
        printf("Error! opening file");            
    }else{
        //Print and close the file
        fprintf(fptr,"%s",finalString);
        fclose(fptr);
    }

}

/*====== Retriece Save ======*/
/**
 * @brief Separate the different data
 * 
 * @param input   The string containing the data frome the file
 * @param output  The array of strings containing the data
 */
void parseTheFile(char input[], char output[4][1024]){
    int size = 0;
    for (unsigned int i = 0; i < 2050; i++){
        if (input[i]=='$'){
            break;
        }else{
            size ++;
        }
    }
    int x = 0;
    int y = 0;
    for (unsigned int i = 0; i < size ;i++){
        if (input[i]=='|'){
            x++;
            y=0;
        }/*else if (input[i]=='$'){
            break;
        }*/else{
            output[x][y] = input[i];
            y++;
        }
    }
}

/**
 * @brief Separate the string into the array for the pieces
 * 
 * @param input     The string to parse
 * @param output    The array to fill
 */
void parseThePieces(char input[], int output[4][21]){
    int size = 0;
    for (unsigned int i = 0; i < 1024; i++){
        if (input[i]=='%'){
            break;
        }else{
            size ++;
        }
    }

    int x = 0;
    int y = 0;
    for (unsigned int i = 0; i < size ;i++){
        if (input[i]=='-'){
            x++;
            y=0;
        }else{
            output[x][y] = input[i] - '0';
            y++;
        }
    }
}

/**
 * @brief Parse the string board into a 2D array
 * 
 * @param input     A string board
 * @param output    A 2D array
 */
void parseTheBoard(char input[], int output[22][22]){
    int size = 0;
    for (unsigned int i = 0; i < 1024; i++){
        if (input[i]=='%'){
            break;
        }else{
            size ++;
        }
    }
    int x = 0;
    int y = 0;
    for (unsigned int i = 0; i < size ;i++){
        if (input[i]=='-'){
            x++;
            y=0;
        }else{
            output[x][y] = input[i] - '0';
            y++;
        }
    }
}

/**
 * @brief Retrieve the game from a file
 * 
 * @param board             2D array with the actual board
 * @param playerturn        poiter to an int of the player it is the turn
 * @param piece_restante    2D array with the pieces of each player
 */
void readSave(int *playerturn, int piece_restante[4][21], int board[22][22]){
    FILE *fptr;
    char readed[2050];
    char readedParsed [4][1024];

    //Open the file
    if ((fptr = fopen("./save.txt","r")) == NULL){
        //log error
        printf("Error! opening file");
    }else{
        //Read data and close the file
        fscanf(fptr,"%s", &readed);
        fclose(fptr); 

        //Parse the data
        parseTheFile(readed,readedParsed);

        //assign playerturn
        *playerturn = atoi(readedParsed[0]);

        //Assign the left pieces
        parseThePieces(readedParsed[1],piece_restante);

        // assign the board
        parseTheBoard(readedParsed[2],board);

        

    }
    
}