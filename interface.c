#include <stdio.h>
#include "student.h"
#include "file_ops.h"
#include "utils.h"

void interface(){
    struct Student student[MAX_STUDENTS];
    int count = load_students(student);
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
        choice = get_valid_int("Enter choice: ", 0, 6);
        

        switch(choice){
            case 1:
                add_student(student, &count);
            break;

            case 2:
                display_students(student, &count);
                printf("\nPress Enter to continue.....");
                getchar();
            break;

            case 3:
            {
                int search_id = get_valid_int("Enter student id to search: ", 1, 1000);

                int index = search_student(student, count, search_id);

                if(index != -1){
                    printf("\n=====Student Found====\n");
                    printf("    ID: %d\n", student[index].id);
                    printf("    Name: %s\n", student[index].name);
                    printf("    Semester: %d\n", student[index].semester);
                    printf("    Course: %s\n", student[index].course);
                } else {
                    printf("\nStudent with ID %d not found!!\n", search_id);
                    printf("Tip: Use option 2 to see all students and their IDS");
                }
            }
            break;

            case 4:
            {
                int delete_id = get_valid_int("Enter student ID to delete: ", 1, 1000);

                delete_student(student, &count, delete_id);
            }
            break;

            case 5:
                update_student(student, count);
            break;

            case 6:
                save_students(student, count);
            break;

            case 0:
                save_students(student, count);
                printf("Exiting.....\n");
            break;

            default:
                printf("Invalid input!!!\n\n Select either 1, 2, 3, 4 or 0!!\n");
            break;

            }

    } while(choice != 0);

    printf("Goodbye!!!\n");

}