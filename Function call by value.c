#include <stdio.h>
int main() {
    /*Creating the variables*/
    int mymult();
    int retval;

/* Assigning 6 and 7 to mymult
While retval is assigned the results of mymult*/
    retval = mymult(6, 7);
/* the printf looks for an integer %d and that references "retval" for what inteager to place there*/
    printf("Answer: %d\n", retval);

}
/* assigning a and b the numbers proided in mymult */
int mymult(a,b)
    /* type of parameters.... in this case a will be a number and we are telling C it's an integer */
    int a,b; 
{
/* this is delcaring c to be a multiplied by b*/
    int c = a * b;
    return c;

}
