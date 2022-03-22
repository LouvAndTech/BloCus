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

#include"test_pos.h"

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
    int realPos[2] = {pos[0]-1, pos[1]-1};
    //Init the varaibale for close enought
    int closeEnougth = 0;

    //For each case in the case 
    for (int piece_h = 0; piece_h < SIZE_PIECE; piece_h++){
        for (int piece_v = 0; piece_v < SIZE_PIECE; piece_v++){
            if(piece[piece_h][piece_v]==1 && board[piece_h+realPos[0]][piece_v+realPos[1]]!=0){
                return(0);
            }
            if (piece[piece_h][piece_v]==2 && board[piece_h+realPos[0]][piece_v+realPos[1]]==player){
                closeEnougth=1;
            }
            if (piece[piece_h][piece_v]==3 && board[piece_h+realPos[0]][piece_v+realPos[1]]==player){
                return(0);
            }
        }
    }
    return(closeEnougth);
}

