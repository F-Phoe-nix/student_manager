#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

struct Student
{
    int id; 
    char name[50];
    int semester;
    char course[100];
};

void add_student(struct Student *students, int *count);
void display_students(struct Student *students, int *count);
int search_student(struct Student *students, int count, int id);
void delete_student(struct Student *students, int *count, int id);
void update_student(struct Student *students, int count);

#endif