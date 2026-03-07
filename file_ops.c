#include <stdio.h>
#include "file_ops.h"

void save_students(struct Student *students, int count) {

    FILE *fp = fopen("students.dat", "wb");
    if(fp == NULL) {
        printf("Error in opening the file!!\n");
        return;
    }

    size_t written = fwrite(students, sizeof(struct Student), count, fp);
    if(written != count) {
        printf("Error: Only saved %zu of %d records.\n", written, count);
    } else {
        printf("Successfully saved %d students to students.dat\n", count);
    }
    fclose(fp);
}

int load_students(struct Student *students) {

    FILE *fp = fopen("students.dat", "rb");
    if(fp == NULL) {
        printf("No students loaded\n");
        return 0;
    }

    int count = fread(students, sizeof(struct Student), MAX_STUDENTS, fp);
    fclose(fp);

    printf("Loaded %d students", count);

    return count;
}