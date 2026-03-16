#include "student.h"
#include <stdio.h>
#include "utils.h"

#define MIN_SEM 1
#define MAX_SEM 10

void add_student(sqlite3 *db) {
    char name[50];
    int semester;
    char course[100];
    
   get_valid_string(name, 50, "Enter Name: ");
   semester = get_valid_int("Enter Semester: ", MIN_SEM, MAX_SEM);
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

int search_student(sqlite3 *db, int id) {
    const char *sql = "SELECT * FROM students WHERE ID = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "\nFailed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_int(stmt, 1, id);

    int result = sqlite3_step(stmt);
    if(result == SQLITE_ROW) {
        printf("\n=== Student ===\n");
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        int semester = sqlite3_column_int(stmt, 2);
        const char *course = (const char *)sqlite3_column_text(stmt, 3);
        
        printf("    ID: %d\n", id);
        printf("    Name: %s\n", name);
        printf("    Semester: %d\n", semester);
        printf("    Course: %s\n", course);
        printf("-------------------------------\n");
    } else {
        printf("\nStudent with ID %d not found\n", id);
    }

    sqlite3_finalize(stmt);

    return result;
}

void delete_student(sqlite3 *db) {
    int id = get_valid_int("Enter ID to delete: ", 1, 1000);

    const char *sql = "DELETE FROM students WHERE ID = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "\nFailed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    int result = sqlite3_step(stmt);

    if(result == SQLITE_DONE) {
        int changes = sqlite3_changes(db);

        if(changes > 0) {
            printf("\nStudent with ID: %d Successfully deleted\n", id);
        } else {
            printf("\nStudent with ID: %d not found\n", id);
        }
    }

    sqlite3_finalize(stmt);
}

void update_student(sqlite3 *db) {
    int id = get_valid_int("Enter ID to update: ", 1, 1000);

    if(search_student(db, id) != SQLITE_ROW) {
        return;
    } 

    printf("\nWhat do you want to update: \n");
    printf("    1. Name\n");
    printf("    2. Semester\n");
    printf("    3. Course\n");  

    int choice = get_valid_int("Enter your choice: ", 1, 3);
    
    const char *sql = NULL;
    sqlite3_stmt *stmt;
    char new_string[100];
    int new_int;

    switch(choice) {
        case 1: sql = "UPDATE students SET name = ? WHERE id = ?;"; break;
        case 2: sql = "UPDATE students SET semester = ? WHERE id = ?;"; break;
        case 3: sql = "UPDATE students SET course = ? WHERE id = ?;"; break;
        default: printf("\nInvalid input\n"); break;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "\nFailed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (choice == 1 || choice == 3) {
        get_valid_string(new_string, (choice == 1 ? 50 : 100), "Enter new value: ");
        sqlite3_bind_text(stmt, 1, new_string, -1, SQLITE_TRANSIENT);
    } else {
        new_int = get_valid_int("Enter new semester: ", 1, 10);
        sqlite3_bind_int(stmt, 1, new_int);
    }

    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        printf("\nUpdate successful!\n");
    } else {
        fprintf(stderr, "\nUpdate failed: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}