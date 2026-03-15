#ifndef STUDENT_H
#define STUDENT_H
#include <sqlite3.h>

void add_student(sqlite3 *db);
void display_students(sqlite3 *db);
void search_student(sqlite3 *db);
void delete_student(sqlite3 *db);
void update_student(sqlite3 *db);

#endif