#include <stdio.h>

//This program will ask you a number and will display the number you entered

int main() {
    int number; // Declare the variable
        
    printf("What number would you like to enter? "); //Asks what number you want to enter
    scanf("%d", &number); //Will ask you to enter a number

    printf("The number you entered is %d\n", number); // Says the number you entered
    
    return 0; // Return 0 to indicate successful execution
}
