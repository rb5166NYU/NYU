#include <stdio.h>
#include <stdlib.h>  // For atoi function

// Main function with command-line arguments
int main(int argc, char *argv[]) {
    // Check if exactly one command-line argument is provided
    if (argc != 2) {
        printf("Usage: %s <year>\n", argv[0]);
        return 1; // Return with an error code
    }

    // Convert the command-line argument to an integer
    int year = atoi(argv[1]);

    // Check if the year is a leap year
    if ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)) {
        // Print if the year is a leap year
        printf("%d was a leap year\n", year);
    } else {
        // Print if the year is not a leap year
        printf("%d was not a leap year\n", year);
    }

    return 0;
}
