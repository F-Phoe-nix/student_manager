#include <stdio.h>
#include "student.h"
#include "file_ops.h"

void interface(){
    struct StudentNode *head = load_students();
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
                add_student(&head);
            break;

            case 2:
                display_students(head);
                printf("\nPress Enter to continue.....");
                getchar();
            break;

            case 3:
            {
                int search_id;
                printf("\nEnter student id to search: ");
                scanf("%d", &search_id);
                getchar();

                struct StudentNode *found = search_student(head, search_id);

                if(found != NULL){
                    printf("\n=====Student Found====\n");
                    printf("    ID: %d\n", found -> data.id);
                    printf("    Name: %s\n", found -> data.name);
                    printf("    Semester: %d\n", found -> data.semester);
                    printf("    Course: %s\n", found -> data.course);
                } else {
                    printf("\nStudent with ID %d not found!!\n", search_id);
                    printf("Tip: Use option 2 to see all students and their IDS");
                }
            }
            break;

            case 4:
            {
                int delete_id;
                printf("Enter student ID to delete: ");
                scanf("%d", &delete_id);
                getchar();

                delete_student(&head, delete_id);
            }
            break;

            case 5:
                update_student(head);
            break;

            case 6:
                save_students(head);
            break;

            case 0:
                save_students(head);
                free_students(head);
                head = NULL;
                printf("Exiting.....\n");
            break;

            default:
                printf("Invalid input!!!\n\nSelect either 1, 2, 3, 4 or 0!!\n");
            break;

            }

    } while(choice != 0);

    printf("Goodbye!!!\n");

}