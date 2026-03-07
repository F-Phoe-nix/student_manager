#include "student.h"
#include <stdio.h>
#include <string.h>


void add_student(struct Student *students, int *count) {
    if(*count >= MAX_STUDENTS) {
        printf("\nError!! Cannot add more students (maximum %d reached)\n", MAX_STUDENTS);
        return;
    }


    //Get the student id and ensure no duplicates are present
    char id_buffer[20];
    int check_id;
    do {
        printf("Enter ID: ");
        if(fgets(id_buffer, sizeof(id_buffer), stdin) == NULL) continue;

        if(id_buffer[0] == "\n"){
            printf("Error!! ID cannot be empty\n");
        } else if(sscanf(id_buffer, "%d", &check_id) == 1) {
            //Checks for duplicates
            if(!is_duplicate_id(students, *count, check_id)) {
                break;
            }

            printf("Error student with ID: %d already exists\n", check_id);
            printf("Enter a unique ID\n");
        } else {
            printf("Enter a valid number");
        }



    } while(1);
    students[*count].id = check_id;

    //Get the name and validate it is not empty
   do{
        printf("Enter Name: ");
        fgets(students[*count].name, 50, stdin);
        students[*count].name[strcspn(students[*count].name, "\n")] = 0; //grabs the newline character added by fgets

        if(students[*count].name[0] != '\0'){
            break;
        }

        printf("Error!! Name Cannot be empty\n");
   }while(1);

   //Get the semester and validate
   char buffer[10];
    do {
        printf("Enter Semester: ");

        if(fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if(buffer[0] == "\n") {

            printf("Input cannot be empty\n");

        } else if(sscanf(buffer, "%d", &students[*count].semester) == 1){
            
            if(students[*count].semester >= 1 && students[*count].semester <= 10) {
                break;
            }

            printf("Error Semester must be between 1 and 10\n");
        } else {
            printf("Enter a valid number\n");
        } 



    }while(1);


    //Get the course and validate it is not empty
    do{
        printf("Enter Course: ");
        fgets(students[*count].course, 100, stdin);
        students[*count].course[(strcspn(students[*count].course, "\n"))] = 0;

        if(students[*count].course[0] != '\0') {
            break;
        }

        printf("Error!! Cause cannot be empty\n");
    }while(1);
    

    printf("\nSuccessfully added student %s with id %d\n", students[*count].name, students[*count].id);
    (*count)++;

}

void display_students(struct Student *students, int *count) {
    if(*count == 0) {
        printf("\nNo students to display\n");
    } else {
        printf("\n=== Student List ===\n");
        for(int i = 0; i < *count; i++) {
            printf("\nStudent %d:\n", i + 1);
            printf("   ID: %d\n", students[i].id);
            printf("   Name: %s\n", students[i].name);
            printf("   Semester: %d\n", students[i].semester);
            printf("   Course: %s\n", students[i].course);
            printf("------------------------------\n");
        }
    }
}

int search_student(struct Student *students, int count, int id) {
    for(int i = 0; i < count; i++){
        if(students[i].id == id) {
            return i;
        } 
    }

    return -1;
}

void delete_student(struct Student *students, int *count, int id){
    int index = search_student(students, *count, id);

    if(index == -1){
        printf("\nStudent with ID %d not found!!\n", id);

        return;
    }

    for(int i = index; i < *count - 1; i++){
        students[i] = students[i+1];
    }

    (*count)--;

    printf("\nSuccessfuly deleted student with id %d\n", id);
}

void update_student(struct Student *students, int count) {
    int update_id = -1;
    printf("Enter ID: ");
    scanf("%d", &update_id);

    int index = search_student(students, count, update_id);

    if(index == -1){
        printf("\nStudent with ID %d not found\n", update_id);
    } else {
        int choice;
        printf("\nWhat do you want to update: \n");
        printf("    1. Name\n");
        printf("    2. Semester\n");
        printf("    3. Course\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Enter Name: ");
            fgets(students[index].name, 50, stdin);
            students[index].name[strcspn(students[index].name, "\n")] = 0;

            printf("Successfully updated name to %s\n", students[index].name);
        break;

        case 2:
            printf("Enter Semester: ");
            scanf("%d", &students[index].semester);
            getchar();

            printf("Successfully updated semester to %d\n", students[index].semester);
        break;

        case 3:
            printf("Enter Course: ");
            fgets(students[index].course, 100, stdin);
            students[index].course[strcspn(students[index].course, "\n")] = 0;

            printf("Successfully updated course to %s\n", students[index].course);
        break;
        
        default:
            printf("Invalid input\n\n Enter either 1, 2, or 3");
        break;
        }

    }
}

int is_duplicate_id(struct Student *students, int count, int id) {
    for(int i = 0; i < count; i++) {
        if(students[i].id == id ) {
            return 1;
        }
    }

    return 0;
}