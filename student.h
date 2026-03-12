#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int id; 
    char name[50];
    int semester;
    char course[100];
};

struct StudentNode {
    struct Student data;
    struct StudentNode *next;
};

void add_student(struct StudentNode **head);
void display_students(struct StudentNode *head);
struct StudentNode *search_student(struct StudentNode *head, int id);
void delete_student(struct StudentNode **head, int id);
void update_student(struct StudentNode **head);
void free_students(struct StudentNode *head);

#endif