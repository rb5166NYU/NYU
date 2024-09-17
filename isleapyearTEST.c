#include<stdio.h>

// int main is defining the main function
// int number declares a variable named "number" 
int main() {
    int year;

//printf will ask what year you'd like to enter
    printf("Enter a year: ");
//scanf will read the number you enter and assign it to the number variable
//The & provides the address to the number variable so it can be stored there
    scanf("%d", &year);

/*
This line first checks if the year is divisable by 4
Then is will check if the yeat is NOT divisable by 100 BUT is divisable by 400
The && (and) ensure it is divisable by 4 AND then will check to make sure it is not divisable by 100
THEN it will check to make sure it can be divisable by 400 with the || (OR). 
Meaning either divisable by 4 OR 400 but NOT 100.
*/
    if ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)) {
// The %d tells the printf to expect an integer value
// The \n moves the cursor to the next line after printing the text
// "number" is the variable that will be assigned to the %d
        printf("%d was a leap year", year);
    } else {
        printf("%d was not a leap year", year);
    }
    
    
    return 0;

}
