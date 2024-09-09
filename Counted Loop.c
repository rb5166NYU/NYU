#include <stdio.h>
int main() {
    int i; /* defines the variable i */
    for(i=0; i<5; i++) { 
      /* "i=0" defines the variable it sets i to 0
          "i<5 is the test for if the loop should continue to run... If i is less than 5
          "i++" each time loop is ran i is increased by 1
          Once the loop has ran enough times to equal 5, it will stop*/
        printf("%d\n",i);
    }
}
