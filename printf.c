#include <stdio.h>
/* This is a comment */

int main() {
/* comments next to the line will show the intented output */
  
  printf("Hello world\n"); /* Hello World */
  printf("Answer %d\n", 42); /* Answer 42 */
  printf("Name %s\n", "Ryan"); /* Name Ryan */
  /* the %.1f instructs the function to print a floating-point number with one digit after the decimal point.
  More specifically for %.1f will dictate how many decimal spots you have. If I change it to 5 there will then be 5 decimal spots*/
  /* %d indicates it is an integer..a number */
  printf("x %.1f i %d\n", 3.5, 100); /* x 3.5 i 100 */

}

