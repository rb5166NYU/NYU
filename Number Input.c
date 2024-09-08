#include <stdio.h>
int main() {
    int usf, euf; /* Defines the usf and euf variables */
     printf("Enter US Floor\n"); /* prints the string specified here */
    scanf("%d", &usf); /* asks for a integer input and will define that to usf with "&" */
    euf = usf - 1; /* defines that euf is usf minus 1 */
    printf("EU Floor %d\n", euf); /* will pring the string "EU Floor and the number we did for the input. the %d is the placeholder for that number and we take that from the euf*/
}
