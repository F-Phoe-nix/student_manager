#include <stdio.h>
#include "student.h"
#include "db.h"
#include "utils.h"

void interface(){
    sqlite3 *db = db_open("students.db");

    if(db == NULL) {
        return;
    }

    if(db_init(db) != 0) {
        db_close(db);
        return;
    }

    int choice;

    do{
        printf("\n========= Student Management System ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        //printf("6. Save to file\n");
        printf("0. Exit\n");
        
        choice = get_valid_int("Enter Choice: ", 0, 6);

        switch(choice){
            case 1:
                add_student(db);
            break;

            case 2:
                display_students(db);
                printf("\nPress Enter to continue.....");
                getchar();
            break;

            case 3:
            {
                int id = get_valid_int("Enter ID to search: ", 1, 1000);

                if(search_student(db, id) != SQLITE_ROW) {
                    printf("\nStudent with ID: %d not found\n", id);
                }
                printf("\nPress Enter to continue.....");
                getchar();
            }
            break;

            case 4:
                delete_student(db);
            break;

            case 5:
                update_student(db);
            break;

            case 6:
                //save_students(db);
            break;

            case 0:
                printf("Exiting.....\n");
            break;

            default:
                printf("Invalid input!!!\n\nSelect either 1, 2, 3, 4 or 0!!\n");
            break;

            }

    } while(choice != 0);

    db_close(db);

    printf("Goodbye!!!\n");

}