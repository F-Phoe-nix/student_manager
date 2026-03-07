#ifndef FILE_OPS_H
#define FILE_OPS_H
#include "student.h"

void save_students(struct Student *students, int count);
int load_students(struct Student *students);
#endif