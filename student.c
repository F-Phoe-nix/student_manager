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

//Main functions
void add_student(struct StudentNode **head) {
    struct StudentNode *new_node = malloc(sizeof(struct StudentNode));

    if(new_node == NULL){
        printf("Error: Memory allocation failed\n");
        return;
    }

    //Get the student id and ensure no duplicates are present
    new_node -> data.id = get_unique_id(*head); //stores the captured data into the struct

    //Get the name and validate it is not empty
   get_valid_string(new_node->data.name, 50, "Enter Name: ");
   
   //Get the semester and validate
   new_node -> data.semester = get_valid_int("Enter Semester: ", MIN_SEM, MAX_SEM);

    //Get the course and validate it is not empty
    get_valid_string(new_node -> data.course, 100, "Enter Course: ");

    new_node -> next = *head;
    *head = new_node;
    
    printf("\nSuccessfully added student %s with id %d\n", new_node -> data.name, new_node -> data.id);
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
        printf("    ID: %d\n", current -> data.id);
        printf("    Name: %s\n", current -> data.name);
        printf("    Semester: %d\n", current -> data.semester);
        printf("    Course: %s\n", current -> data.course);
        printf("-------------------------------\n");

        current = current -> next;
        count++;
    }
}

struct StudentNode *search_student(struct StudentNode *head, int id) {
    struct StudentNode *current = head;

    while(current != NULL){
        if(current -> data.id == id) {
            return current;
        }

        current = current -> next;
    }

    return NULL;
}

void delete_student(struct StudentNode **head, int id) {}

void update_student(struct StudentNode **head) {}

void free_students(struct StudentNode *head) {}

int count_students(struct StudentNode *head) {}
