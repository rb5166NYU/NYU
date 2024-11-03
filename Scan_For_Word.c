#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int found = 0;

    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (strstr(buffer, "confidential") != NULL) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("The word 'confidential' was found in the file.\n");
    } else {
        printf("The word 'confidential' was not found in the file.\n");
    }

    return 0;
}
