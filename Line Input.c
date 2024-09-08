#include <stdio.h>
int main() {
    char line[1001];/* an array defined as "line" that will take up to 1001 characters */
    printf("Enter line\n");/* prompts user */
    scanf("%1000[^\n]s", line);
    /* [^\n] means match any character that's not a new line... 
    scan up to the end of a line... 
    Or until you hit 1000 character (defined with the 1000)*/
    printf("Line: %s\n", line); /* */
}
