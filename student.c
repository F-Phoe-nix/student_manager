#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static int get_unique_id(struct StudentNode *head) {
    int get_id;
    do{
        get_id = get_valid_int("Enter ID: ", MIN_ID, MAX_ID);

        if(search_student(head, get_id) == NULL){
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

int count_students(struct StudentNode *head) {
    int count = 0;

    struct StudentNode *current = head;

    while(current != NULL) {
        count++;
        current = current -> next;
    }

    return count;
}

//Main functions
void add_student(struct StudentNode **head) {
    struct StudentNode *new_node = malloc(sizeof(struct StudentNode));

    if(new_node == NULL){
        printf("Error: Memory allocation failed\n");
        return;
    }

    //Get the student id and ensure no duplicates are present
    new_node->data.id = get_unique_id(*head); //stores the captured data into the struct

    //Get the name and validate it is not empty
   get_valid_string(new_node->data.name, 50, "Enter Name: ");
   
   //Get the semester and validate
   new_node->data.semester = get_valid_int("Enter Semester: ", MIN_SEM, MAX_SEM);

    //Get the course and validate it is not empty
    get_valid_string(new_node->data.course, 100, "Enter Course: ");

    if(*head == NULL || new_node->data.id < (*head)->data.id) {
        new_node->next = *head;
        *head = new_node;
    } else {
        struct StudentNode *current = *head;

        while(current->next != NULL && current->next->data.id < new_node->data.id) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    printf("\nSuccessfully added student %s with id %d\n", new_node->data.name, new_node->data.id);
}

void display_students(struct StudentNode *head) {
    if(head == NULL) {
        printf("\nNo students to display\n");
        return;
    }

    printf("\n=== Student List ===\n");
    
    struct StudentNode *current = head;
    int count = 1;
    
    while(current != NULL) {
        printf("\nStudent: %d\n", count);
        printf("    ID: %d\n", current->data.id);
        printf("    Name: %s\n", current->data.name);
        printf("    Semester: %d\n", current->data.semester);
        printf("    Course: %s\n", current->data.course);
        printf("-------------------------------\n");

        current = current -> next;
        count++;
    }
}

struct StudentNode *search_student(struct StudentNode *head, int id) {
    struct StudentNode *current = head;

    while(current != NULL){
        if(current->data.id == id) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void delete_student(struct StudentNode **head, int id) {
    if(*head == NULL) {
        printf("\nNo students to delete\n");
        return;
    }

    if((*head)->data.id == id) {
        struct StudentNode *temp = *head;
        *head = (*head)->next;
        free(temp);

        printf("\nSuccessfully deleted student with ID: %d\n", id);

        return;
    }

    struct StudentNode *current = *head;

    while (current->next != NULL && current->next->data.id != id) {
        current = current->next;
    }
    
    if(current->next == NULL) {
        printf("\nDelete failed: Student with ID: %d not found!\n", id);
        printf("\nTip! Use option 2 to display all students!!\n");
    } else {
        struct StudentNode *temp = current->next;

        current->next = current->next->next;
        free(temp);

        printf("\nSuccessfully deleted student with ID: %d\n", id);
    }
    
}

void update_student(struct StudentNode *head) {
    int update_id = get_valid_int("Enter ID to update: ", MIN_ID, MAX_ID);

    struct StudentNode *update = search_student(head, update_id);

    if(update == NULL) {
        printf("\nStudent with ID: %d not found\n", update_id);
    } else {
        printf("What do you want to update: \n");
        printf("    1. Name\n");
        printf("    2. Semester\n");
        printf("    3. Course\n");

        int choice = get_valid_int("Enter your choice: ", 1, 3);

        switch (choice)
        {
        case 1:
            get_valid_string(update->data.name, 50, "Enter New Name: ");
            printf("\nSuccessfully updated name of student with ID: %d to %s\n", update_id, update->data.name);
        break;

        case 2:
            update->data.semester = get_valid_int("Enter New Semester: ", MIN_SEM, MAX_SEM);
            printf("\nSuccessfully updated semester of student with ID: %d to %d\n", update_id, update->data.semester);
        break;

        case 3:
            get_valid_string(update->data.course, 100, "Enter New Course: ");
            printf("\nSuccessfully updated course of student with ID: %d to %s\n", update_id, update->data.course);
        break;
        
        default:
            printf("\nInvalid input!!\n\nEnter Either 1, 2 or 3!!\n");
        break;
        }
    }
}

void free_students(struct StudentNode *head) {
    struct StudentNode *current = head;
    struct StudentNode *next_node;

    int count = count_students(current);

    while(current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    printf("\nFreed %d, student records\n", count);
}
