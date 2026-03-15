#ifndef DB_H
#define DB_H
#include <sqlite3.h>

sqlite3 *db_open(const char *filename);
void db_close(sqlite3 *db);
int db_init(sqlite3 *db);

#endif