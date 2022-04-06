#include <stdio.h>
#include "sqlite/sqlite3.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}

typedef struct{
    int id; //ID de la sauvgarde
    int player_turn; //Wich player is suposed to play next
    int piece_restante[4][21]; //Each line for a player and each column a piece
    int board[22][22]; //The actual state of the board
}data;

// void savegame(int board[22][22],int player,int playerlist[4]){
//     // donne = formatData();
//     // addRow(donne);
// }

void creatTable(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    rc = sqlite3_open("./file.db",&db);


    sql="CREATE TABLE Save(id INT,player_turn INT, piece_restante INT ,board INT);";

    //Execute sql statements
    rc=sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr,"SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        fprintf(stdout,">>> Table created sucessfully\n");
    }
}

void deleteTable(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    rc = sqlite3_open("./file.db",&db);

    sql="DROP TABLE Save;";

    //Execute sql statements
    rc=sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr,"SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        fprintf(stdout,">>> Table deleted sucessfully\n");
    }
}

// data formatData(int board[22][22], int player, data PlayerL){
//     data donnees;
//
//     donnees.board[22][22] = board;
//     donnees.player_turn = player;
//     donnees.piece_restante[4][22] = ;
//
//     return donnees;
// }

void addRow(int id, int player, int piece_restante, int* board){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    char boardChar[24] = "test bitch";

    //open db
    rc = sqlite3_open("./file.db",&db);

    if(rc){
        fprintf(stderr, ">>> Can't open database!: %s\n", sqlite3_errmsg(db));
    }
    //add data a new row
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "INSERT INTO Save (id,player_turn,piece_restante,board) VALUES (%d,%d,%d,%s)",id,player,piece_restante,boardChar);
    printf("\n>>> %s <<<\n",buffer);
    sql=buffer;

    rc=sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    //close db
    sqlite3_close(db);
}

int main(int argc, char **argv){
    int piece_restante[4][21];
    int board[22][22];
    deleteTable();
    creatTable();

    addRow(1,2,3,*board);

    return 0;