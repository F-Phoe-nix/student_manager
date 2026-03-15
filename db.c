#include "db.h"
#include <stdio.h>

sqlite3 *db_open(const char *filename) {
    sqlite3 *db = NULL;
    int rc = sqlite3_open(filename, &db); 

    if(rc != SQLITE_OK) {
        fprintf(stderr, "\nCan't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    printf("Successfully opened the database");
    return db;
}

void db_close(sqlite3 *db) {
    if(db == NULL) {
        printf("\nDatabase already closed or was never opened\n");
        return;
    }

    int rc = sqlite3_close(db);

    if(rc == SQLITE_OK) {
        printf("\nSuccessfully closed the database\n");
    } else {
        fprintf(stderr, "\nFailed to close the database: %s\n", sqlite3_errmsg(db));
    }
}

int db_init(sqlite3 *db) {
    const char *sql =
    "CREATE TABLE IF NOT EXISTS students ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "name TEXT NOT NULL,"
    "semester INTEGER NOT NULL CHECK(semester between 1 and 10),"
    "course TEXT NOT NULL"
    ");";

    char *err_msg = NULL;
    int code = sqlite3_exec(db, sql, NULL, NULL, &err_msg);

    if(code != SQLITE_OK) {
        fprintf(stderr, "\nError in creating table: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    printf("\nTable Creation successful\n");
    return 0;
}