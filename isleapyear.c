#include <stdio.h>
/* 
- This header stdlib will allow the conversion from ASCII to integer... makes string to and int 
- If you want to use command line to enter numbers to feed into program, you need this header. It is the means for converting the command line numbers (entered as a string) into integers.
*/
#include <stdlib.h>  // For atoi function

// Main function with command-line arguments
/* 
- the "argc" argument count is the number of command line arguments 
- the "char" is for character or the data type used to represent individual characters
- The "argv" is argument vector this is an array of strings representing arguments passed to program
- Ultimatlly "int main(int argc, char *argv[])" is allowing the program to accept command line arguments 
argc tells us how many arguments passed while argv tells us the values of those arguments passed
*/
int main(int argc, char *argv[]) {
    // Check if exactly one command-line argument is provided
    /* Makes sure there isn't more than 1 argument (argc) provided */
    if (argc != 2) {
/* 
- To inform user how program works  
- Prints Usage and the program name
- the %s will look for a string and the argv[0] is from the first command line argument entered...(The program name)
- <year> is printed to instruct the user that they should enter a year
*/
        printf("Usage: %s <year>\n", argv[0]);
        return 1; // Return with an error code
    }

    // Convert the command-line argument to an integer
/*
- creates the integer (int) variable(year). 
- atoi converts string to integer. This is neccisary because command line takes in strings not integers. Our program is looking to preform calculations with integers.
- the atoi convers the second [1] command line variable entered into an integer. So if we enter "2022" it will be stored as an integer
*/
    int year = atoi(argv[1]);

    // Check if the year is a leap year
/*
- first checks if the year is divisable by 4
- Then will check if the year is NOT divisable by 100 BUT is divisable by 400
- The && (and) ensure it is divisable by 4 AND then will check to make sure it is not divisable by 100
- THEN it will check to make sure it can be divisable by 400 with the || (OR). 
- Meaning either divisable by 4 OR 400 but NOT 100.
*/
    if ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)) {
        // Print if the year is a leap year
        printf("%d was a leap year\n", year);
    } else {
        // Print if the year is not a leap year
        printf("%d was not a leap year\n", year);
    }

    return 0;
}
