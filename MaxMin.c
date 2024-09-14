/// Note this doesn't work, note sure what the issue is.

#include <stdio.h>
int main() {
    int first = 1;
    int val, maxval, minval;

    while(scanf("%d",&val) != EOF) { /* &val is used to replace the current assigned value for val */
        if ( first || val > maxval ) maxval = val;
        if ( first || val < minval ) minval = val;
        first = 0;
    }

    printf("Maximum %d\n", maxval);
    printf("Minumum %d\n", minval);
    
}
