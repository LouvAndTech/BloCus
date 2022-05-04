/**
 * @file test_pos.c
 * @author Elouan Lérissel
 * @brief test file 
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include"boardXpiece.h"

#define SIZE_BOARD 22
#define SIZE_PIECE 7

/**
 * @brief function to check if you can place the piece at a definie place
 * 
 * @param board     a 2D array with the actual state of the board
 * @param piece     a 2D array with the piece you want to use in the pos you want to use
 * @param pos       a 1D array with [0]=the pos on x and [1]=the pos on Y
 * @param player    a int containing the number of the player
 * @return int      1 if possible else 0 
 */
int checkPos(int board[SIZE_BOARD][SIZE_BOARD], int piece[SIZE_PIECE][SIZE_PIECE],int pos[2],int player){
    //Get the real position on the board
    int posMasquePiece[2] = {pos[0]-1, pos[1]-1};
    int posInTab[2];
    //Init the varaibale for close enought
    int closeEnougth = 0;
    //Init the varaibale to know if the player can play
    int placeOK = 1;

    //For each case in the piece 
    for (int piece_h = 0; piece_h < SIZE_PIECE && placeOK; piece_h++){
                posInTab[0] = piece_h+posMasquePiece[0];
        for (int piece_v = 0; piece_v < SIZE_PIECE && placeOK; piece_v++){
            //Calculate the pos on the board we're looking for
            posInTab[1] = piece_v+posMasquePiece[1];
            switch (piece[piece_h][piece_v]){
                //Check for collisions
                case 1:
                    if (board[posInTab[0]][posInTab[1]]!=0){
                        placeOK = 0;
                    }
                    break;
                //check for close enought to it's own pieces
                case 2:
                    if (board[posInTab[0]][posInTab[1]]==player){
                        closeEnougth = 1;
                    }
                    break;
                //check for far enought from it's own pieces
                case 3:
                    if (board[posInTab[0]][posInTab[1]]==player){
                        placeOK = 0;
                    }
                    break;
            }
        }
    }
    return((closeEnougth && placeOK)?1:0);
}

/**
 * @brief Place a piece on the board
 * 
 * @param tab       //a 2D array with the actual state of the board
 * @param piece     //a 2D array with the piece you want to use
 * @param pos       //a 1D array with [0]=the pos on x and [1]=the pos on Y
 * @param player    //a int containing the number of the player
 */
void placePiece(int tab[SIZE_BOARD][SIZE_BOARD],int piece[7][7],int pos[2],int player){
    //Get the real position on the board
    int realPos[2] = {pos[0]-1, pos[1]-1};
    //For each case in the case 
    for (int piece_h = 0; piece_h < SIZE_PIECE; piece_h++){
        for (int piece_v = 0; piece_v < SIZE_PIECE; piece_v++){
            if(piece[piece_h][piece_v]==1){
                tab[piece_h+realPos[0]][piece_v+realPos[1]]=player+1;
            }
        }
    }
}

/**
 * @brief Funciton to check if the player as win
 * 
 * @param pieces    //a 1D array with the list of remaining pieces
 * @return int      //1 if the player win else 0
 */
int checkWin(int pieces[21]){
    for (int i = 0; i < 21; i++){
        if(pieces[i]!=0){
            return(0);
        }
    }
    return(1);
}

/**
 * @brief Funciton to check if the player can still play
 * 
 * @param tab    //a 2D array with the actual state of the board
 * @param pieces //a 1D array with the list of remaining pieces
 * @param player //a int containing the number of the player
 * @return int      //1 if the player as loos else 0
 */
int blocked(int tab[SIZE_BOARD][SIZE_BOARD],int pieces[21],int player){
    int pos[2];
    int changedPiece[7][7]; //Piece to store the change 
    int tabPiece[7][7]; //Piece to store the piece

    //for each piece
    for (int p = 0; p < 21; p++){
        //if the piece is not used
        if (pieces[p] == 1){
            returnPiece(tabPiece, p);
            //for each case of the board
            for (int i = 0; i < SIZE_BOARD; i++){
                for (int j = 0; j < SIZE_BOARD; j++){
                    pos[0] = i ; pos[1] = j;
                    //for each miror of the piece
                    for (int mr = 0; mr < 2; mr++){
                        //for each rotation of the piece
                        for (int rt = 0; rt < 3; rt++){
                            //Check if it's possible
                            if(checkPos(tab,tabPiece,pos,player+1)==1){
                                return(0);
                            }
                            //Rotate right
                            rotateRigth(tabPiece,changedPiece);
                            //copy to the actual piece
                            copy(changedPiece,tabPiece);
                        }
                    //miror
                    miror(tabPiece,changedPiece);
                    //copy
                    copy(changedPiece,tabPiece);
                    }
                }
            }
        }
    }
    return(1);
}
    