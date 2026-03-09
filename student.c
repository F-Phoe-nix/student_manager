#include "student.h"
#include <stdio.h>
#include <string.h>

#define MIN_ID 1
#define MAX_ID 10000
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

static int get_unique_id(struct Student *students, int count) {
    int get_id;
    do{
        get_id = get_valid_int("Enter ID: ", MIN_ID, MAX_ID);

        if(search_student(students, count, get_id) == -1){
            return get_id;
        } else {
            printf("Error!! student with ID: %d already exists\n", get_id);
            printf("Enter a unique value\n");
        }
    } while(1);
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




void add_student(struct Student *students, int *count) {
    if(*count >= MAX_STUDENTS) {
        printf("\nError!! Cannot add more students (maximum %d reached)\n", MAX_STUDENTS);
        return;
    }

    //Get the student id and ensure no duplicates are present
    students[*count].id = get_unique_id(students, *count); //stores the captured data into the struct

    //Get the name and validate it is not empty
   get_valid_string(students[*count].name, 50, "Enter Name: ");
   
   //Get the semester and validate
   students[*count].semester = get_valid_int("Enter Semester: ", MIN_SEM, MAX_SEM);

    //Get the course and validate it is not empty
    get_valid_string(students[*count].course, 100, "Enter Course: ");
    
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
        printf("Tip: use option 2 to see all available students\n");

        return;
    }

    for(int i = index; i < *count - 1; i++){
        students[i] = students[i+1];
    }

    (*count)--;

    printf("\nSuccessfuly deleted student with id %d\n", id);
}

void update_student(struct Student *students, int count) {
    int update_id = get_valid_int("Enter ID of student to update: ", MIN_ID, MAX_ID);

    int index = search_student(students, count, update_id);

    if(index == -1){
        printf("\nStudent with ID %d not found\n", update_id);
    } else {
        printf("\nWhat do you want to update: \n");
        printf("    1. Name\n");
        printf("    2. Semester\n");
        printf("    3. Course\n");
        
        int choice = get_valid_int("Enter your choice: ", 1, 3);

        switch (choice) {
        case 1:
            get_valid_string(students[index].name, 50, "Enter New Name: ");
            printf("Successfully updated name of student with ID: %d to %s\n", update_id, students[index].name);
        break;

        case 2:
            students[index].semester = get_valid_int("Enter New Semester: ", MIN_SEM, MAX_SEM);
            printf("Successfully updated semester of student with ID: %d to %d\n", update_id, students[index].semester);
        break;

        case 3:
            get_valid_string(students[index].course, 100, "Enter New Course: ");
            printf("Successfully updated semester of student with ID: %d to %s\n", update_id, students[index].course);
        break;
        
        default:
            printf("Invalid input\n\nEnter either 1, 2, or 3\n");
        break;
        }

    }
}
