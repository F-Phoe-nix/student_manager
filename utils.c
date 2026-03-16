#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_valid_int(char *prompt, int min, int max) {
    do
    {
        char buffer[20];
        int value;

        printf("%s", prompt);
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        if(strchr(buffer, '\n') == NULL) {
            int c;
            while((c = getchar()) != '\n' && c != EOF);
            printf("\nError!! Input too long\n");
            continue;
        }

        if(sscanf(buffer, "%d", &value) == 1) {
            if(value >= min && value <= max) {
                return value;
            }
            printf("\nError!! Enter a number between %d and %d\n", min, max);
        } else {
            printf("\nError!! Invalid input\n");
        }
    } while (1);
    
}

void get_valid_string(char *dest, int size, const char *prompt) {
    int valid;
    do{
        valid = 1;
        printf("%s", prompt);
        if(fgets(dest, size, stdin) != NULL) {
            dest[strcspn(dest, "\n")] = '\0';

            if(dest[0] == '\0') {
                printf("\nError!! Input cannot be empty\n");
                valid = 0;
                continue;
            }

            for(int i = 0; dest[i] != '\0'; i++) {
                if(!isalpha((unsigned char) dest[i]) && !isspace((unsigned char) dest[i])) {
                    printf("\nError!! Only letters and spaces allowed\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while(!valid);
}