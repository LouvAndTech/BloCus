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

void savegame(int board[22][22],int player,int playerlist[4]){
    // donne = formatData();
    // addRow(donne);
}

void creatTable(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    sql="CREATE TABLE Save(id INT,player_turn INT,piece_restante[4][21] INT,board[22][22] INT);";

    //Execute sql statements
    rc=sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr,"SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        fprintf(stdout,"Table created sucessfully\n");
    }
}

data formatData(int board[22][22], int player, data PlayerL){
    data donnees;

    donnees.board[22][22] = board;
    donnees.player_turn = player;
    donnees.piece_restante[4][22] = ;

    return donnees;
}

void addRow(donnees){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    //open db
    rc = sqlite3_open("./file.db",&db);

    if(rc){
        fprintf(stderr, "Can't open database!: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        fprintf(stdout," Opened database sucessfully\n");
    }

    //add data a new row
    sql="INSERT INTO Save (id, player_turn) VALUES (1,17)";

    rc=sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    //close db
    sqlite3_close(db);
}







int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    //Open database
    rc = sqlite3_open("./file.db",&db);

    if(rc){
        fprintf(stderr, "Can't open database!: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        fprintf(stdout," Opened database sucessfully\n");
    }

    /*Create sql table
    sql="CREATE TABLE Save(id INT,player_turn INT);";

    //Execute sql statements
    rc=sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr,"SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        fprintf(stdout,"Table created sucessfully\n");
    }
    */

    /*Write in the Database*/
    sql="INSERT INTO Save (id, player_turn) VALUES (1,17)";

    rc=sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    sqlite3_close(db);


    //read form db
    rc = sqlite3_open("./file.db",&db);
    sql = "SELECT * FROM Save";
        
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", zErrMsg);

        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        
        return 1;
    }

    sqlite3_close(db);
    return 0;
}