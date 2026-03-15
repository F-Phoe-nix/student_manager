#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_SEM 1
#define MAX_SEM 10

//helper functions
static int get_valid_int(char *prompt, int min, int max) {
    do
    {
        char buffer[10];
        int value;

        printf("%s", prompt);
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if(sscanf(buffer, "%d", &value) == 1) {
            if(value >= min && value <= max) {
                return value;
            }
            printf("Error!! Enter a number between %d and %d\n", min, max);
        } else {
            printf("Error!! Invalid input\n");
        }
    } while (1);
    
}

static void get_valid_string(char *dest, int size, const char *prompt) {
    do{
        printf("%s", prompt);
        if(fgets(dest, size, stdin) != NULL) {
            dest[strcspn(dest, "\n")] = '\0';

            if(dest[0] != '\0') break;
        }
        printf("Error!! Input cannot be empty\n");
    } while(1);
}

//Main functions
void add_student(sqlite3 *db) {
    char name[50];
    int semester;
    char course[100];
    
    //Get the name and validate it is not empty
   get_valid_string(name, 50, "Enter Name: ");
   
   //Get the semester and validate
   semester = get_valid_int("Enter Semester: ", MIN_SEM, MAX_SEM);

    //Get the course and validate it is not empty
    get_valid_string(course, 100, "Enter Course: ");

    const char *sql = "INSERT INTO students(name, semester, course) VALUES (?,?,?);";

    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "\nFailed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }


    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, semester);
    sqlite3_bind_text(stmt, 3, course, -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);

    if(result != SQLITE_DONE) {
        fprintf(stderr, "\nExecution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("\nSuccessfully added student %s\n", name);
    }

    sqlite3_finalize(stmt);
}

void display_students(sqlite3 *db) {
    const char *sql = "SELECT * FROM students ORDER BY ID;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "\nFailed to preparing statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== Student List ===\n");

    int count = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        int semester = sqlite3_column_int(stmt, 2);
        const char *course = (const char *)sqlite3_column_text(stmt, 3);

        count++;
        printf("\nStudent: %d\n", count);
        printf("    ID: %d\n", id);
        printf("    Name: %s\n", name);
        printf("    Semester: %d\n", semester);
        printf("    Course: %s\n", course);
        printf("-------------------------------\n");
    }

    if(count == 0) {
        printf("\nNo students found\n");
    }

    sqlite3_finalize(stmt);
}

void search_student(sqlite3 *db) {
    //const char *sql = "SELECT * FROM students WHERE ID ==;";
}

void delete_student(sqlite3 *db) {}

void update_student(sqlite3 *db) {}
