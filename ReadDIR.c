#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Could not open file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *directory_path = argv[1];
    DIR *dir = opendir(directory_path);
    if (dir == NULL) {
        perror("Could not open directory");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct stat fileStat;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the '.' and '..' entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path of the file
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", directory_path, entry->d_name);

        // Use stat to check if it's a regular file
        if (stat(filepath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            printf("\n Reading file: %s\n", filepath);
            read_file(filepath);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}
