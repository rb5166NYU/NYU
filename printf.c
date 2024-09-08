#include <stdio.h>
/* This is a comment */

int main() {
/* comments next to the line will show the intented output */
  /* the \n is what says to print a new line, if removed they will all be in the same line */
  printf("Hello world\n"); /* Hello World */
  /* the %d is telling us there is an integer (number) and to convert that into a string */
  printf("Answer %d\n", 42); /* Answer 42 */
  /* The %s is saying there an array of character (string)  */
  printf("Name %s\n", "Ryan"); /* Name Ryan */
  /* the %.1f instructs the function to print a floating-point number with one digit after the decimal point.
  More specifically for %.1f will dictate how many decimal spots you have. If I change it to 5 there will then be 5 decimal spots*/
  /* %d indicates it is an integer..a number */
  /* To tie the bottom together... the %.1f will take in the first number specified (the 3.5) while.
  While the %d will take in the second number specified (the 100)
  HOWEVER, the %.1f needs a number with a decimal place, while the %d needs a whole number*/
  printf("x %.1f i %d\n", 3.5, 100); /* x 3.5 i 100 */

}

