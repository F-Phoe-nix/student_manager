#include "student.h"
#include <stdio.h>
#include <string.h>

//helper functions
static int get_unique_id(struct Student *students, int count) {
    char id_buffer[20];
    int get_id;
    do{
        printf("Enter ID: ");
        if(fgets(id_buffer, sizeof(id_buffer), stdin) == NULL) continue;

        if(id_buffer[0] == '\n') {
            printf("Error!! ID cannot be empty\n");
        } else if(sscanf(id_buffer, "%d", &get_id) == 1) {
            if(search_student(students, count, get_id) == -1) {
                if(get_id <= 0) {
                    printf("ID must be greater than 0\n");
                } else {
                    return get_id;
                }
            } else {
                printf("Error!! Student with %d ID already exists\n", get_id);
                printf("Enter a unique ID\n");
            }

        } else {
            printf("Enter a valid number\n");
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

static int get_valid_semester() {
    do
    {
        char buffer[10];
        int sem;

        printf("Enter semester (1 - 10): ");
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if(sscanf(buffer, "%d", &sem) == 1) {
            if(sem >= 1 && sem <= 10) return sem;

            printf("Semester must be between 1 and 10\n");
        } else {
            printf("Enter a valid semester\n");
        }
    } while (1);
    
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
   students[*count].semester = get_valid_semester();


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
    int update_id;

    printf("Enter ID of student to update: ");
    if(scanf("%d", &update_id) != 1){
        printf("Inlavid input\n");
        while(getchar() != '\n');
        return;
    }

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
            get_valid_string(students[index].name, 50, "Enter New Name: ");
            printf("Successfully updated name of student with ID: %d to %s\n", update_id, students[index].name);
        break;

        case 2:
            students[index].semester = get_valid_semester();
            printf("Successfully updated semester of student with ID: %d to %d\n", update_id, students[index].semester);
        break;

        case 3:
            get_valid_string(students[index].course, 100, "Enter New Course: ");
            printf("Successfully updated semester of student with ID: %d to %s\n", update_id, students[index].course);
        break;
        
        default:
            printf("Invalid input\n\n Enter either 1, 2, or 3");
        break;
        }

    }
}
