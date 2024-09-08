#include <stdio.h>
int main() {
    char name[100]; /* Declares a character array of 100... the "name" here is the variable being assigned.. The char is saying that assigned variable is an array (of characters) */
    printf("Enter Name\n"); /* Prints a prompt */
    scanf("%100s", name); /* asking for a string (%s) and only read up to 100 character (the 100 between % s). and assigns that input to "name" */
    printf("Hello %s\n", name); /* Prints Hello and then will look for a string and use "name" to fill in that string*/
}


/* NOTE: No need to add a "&" for an array. Using a & defines where to start. An array is technically stating where to start */
