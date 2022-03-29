#include <stdio.h>
#include "sqlite/sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
}

int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /*Open database*/
    rc = sqlite3_open("file.db",&db);

    if(rc){
        fprintf(stderr, "Can't open database!: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        fprintf(stdout," Opened database sucessfully\n");
    }
    return 0;

    /*Create sql statements*/
    sql="CREATE TABLEL COMPANY("
        "ID INT PRIMARY KEY     NOT NULL,"
        "NAME           TEXT    NOT NULL,"
        "AGE            INT     NOT NULL,"
        "ADRESSE        CHAR(50),"
        "SALARY         REAL );";

    /*Execute sql statements*/
    rc=sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr,"SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        fprintf(stdout,"Table created sucessfully\n");
    }
    sqlite3_close(db);
    return 0;
}