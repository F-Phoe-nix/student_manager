#include <stdio.h>
#include "student.h"
#include "db.h"

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
        printf("6. Save to file\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

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
                int search_id;
                printf("\nEnter student id to search: ");
                scanf("%d", &search_id);
                getchar();

                search_student(db);

                // if(found != NULL){
                //     printf("\n=====Student Found====\n");
                //     printf("    ID: %d\n", found -> data.id);
                //     printf("    Name: %s\n", found -> data.name);
                //     printf("    Semester: %d\n", found -> data.semester);
                //     printf("    Course: %s\n", found -> data.course);
                // } else {
                //     printf("\nStudent with ID %d not found!!\n", search_id);
                //     printf("Tip: Use option 2 to see all students and their IDS");
                // }
            }
            break;

            case 4:
            {
                int delete_id;
                printf("Enter student ID to delete: ");
                scanf("%d", &delete_id);
                getchar();

                delete_student(db);
            }
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