#include "utils.h"
#include <stdio.h>
#include <string.h>

int get_valid_int(char *prompt, int min, int max) {
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

void get_valid_string(char *dest, int size, const char *prompt) {
    do{
        printf("%s", prompt);
        if(fgets(dest, size, stdin) != NULL) {
            dest[strcspn(dest, "\n")] = '\0';

            if(dest[0] != '\0') break;
        }
        printf("Error!! Input cannot be empty\n");
    } while(1);
}