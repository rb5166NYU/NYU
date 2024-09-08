#include <stdio.h>
int main() {
    char line[1000]; /* creates a variable array with a limit of 1000 */ 
    FILE *hand; /* FILE is a type assigned by stdio.h... and *hand is a pointer to a file object...  */
    hand = fopen("romeo.txt", "r"); /* fopen will open the file... romeo.txt and r are character arrays... Doesn't have to be romeo, can be anything just make sure file is in same directory*/
    while( fgets(line,1000, hand) != NULL ) { /* call line variable, up to 1000 characters, from the file handle "hand"..... the basicially will read until end of file.... 
    fgets is a type defined in stdio.h that returns NULL*/
        printf("%s", line);
    }

}
