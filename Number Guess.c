#include <stdio.h>
int main() {
    int guess;
    printf("Enter Number Guess\n"); /* This will prompt user */
    
  /* Starts a loop with "while"
  Then will look for user input with scanf.. Looking for number diue to the %d 
  The &guess will store the value entered into scanf
  This will continue until end of file or EOF is reached (Until the if condition is satisfied)*/
  while(scanf("%d",&guess) != EOF )     {  
      /* Creates the if condtion for "guess" to equal "42" */  
      if ( guess == 42 ) {
            printf("Nice Work!\n");
          /* break will end the loop */  
          break;
        }
        /* sets up the "else if" for if the "if" condition isn't meet
        In this case the input of %d from the scanf will determine the printf statment
        the less than < creates that path based on the number being less than 42 or not*/
        else if ( guess < 42 )
            printf("Too low - guess gain\n");
        else
            printf("Too High - guess again\n");


    }


}
