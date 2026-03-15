#ifndef FILE_OPS_H
#define FILE_OPS_H
#include "student.h"

void save_students(struct StudentNode *head);
struct StudentNode *load_students(void);
#endif