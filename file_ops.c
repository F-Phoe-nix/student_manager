#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>

void save_students(struct StudentNode *head) {
    struct StudentNode *current = head;

    FILE *fp = fopen("students.dat", "wb");
    if(fp == NULL) {
        printf("\nError in opening the file!!\n");
        return;
    }

    int count = count_students(head);
    fwrite(&count, sizeof(int), 1, fp);
    
    while(current != NULL) {
        fwrite(&current->data, sizeof(struct Student), 1, fp);
        current = current->next;
    }
    fclose(fp);

    printf("\nSuccessfully saved %d students to file\n", count);
}

struct StudentNode *load_students(void) {

    FILE *fp = fopen("students.dat", "rb");
    if(fp == NULL) {
        printf("\nNo previous data found: Starting a fresh\n");
        return NULL;
    }

    int count;
    if(fread(&count, sizeof(int), 1, fp) != 1) {
        printf("\nError reading file\n");
        fclose(fp);
        return NULL;
    }

    struct StudentNode *head = NULL;
    struct StudentNode *tail = NULL;

    for(int i = 0; i < count; i++) {
        struct StudentNode *new_node = malloc(sizeof(struct StudentNode));
        if(new_node == NULL) {
            printf("\nMemory Allocation failed during load\n");
            break;
        }

        if(fread(&new_node->data, sizeof(struct Student), 1, fp) != 1) {
            free(new_node);
            break;
        }

        new_node->next = NULL;

        if(head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fclose(fp);
    printf("\nSuccessfully loaded %d students\n", count);
    return head;
}