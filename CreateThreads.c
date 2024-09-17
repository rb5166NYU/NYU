/* Includes the POSIX thread library which provides functions for creating and managing threads.*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Sets the number of threads we're creating at 10 and creates a constant named "NUMBER_OF_THREADS" */
#define NUMBER_OF_THREADS 10
/* 
- void will speciofiy that there will be no function returned to caller.. the hello world won't be displayed 
- tid is the identified for each thread
*/
void *print_hello_world(void *tid)
{
/* 
- This function prints the thread's identifier and then exits 
- int thread_id = *((int *)tid);: Casts the void* argument tid back to an int*, then dereferences it to get the integer thread ID. This is necessary because pthread_create passes arguments as void*.
- printf("Hello World. Greetings from thread %d\n", thread_id);: Prints a message including the thread ID.
- free(tid);: Frees the memory allocated for the thread ID. This prevents memory leaks.
- pthread_exit(NULL);: Exits the thread and signifies that it has finished executing. NULL indicates that no exit status is being returned.
*/
    int thread_id = *((int *)tid); // Cast and dereference to get the int value
    printf("Hello World. Greetings from thread %d\n", thread_id);
    free(tid); // Free the allocated memory
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;

    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        printf("Main here. Creating thread %d\n", i);
        
        // Allocate memory for thread id
        int *tid = malloc(sizeof(int));
        if (tid == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *tid = i; // Set the thread id

        status = pthread_create(&threads[i], NULL, print_hello_world, tid);

        if (status != 0) {
            printf("Oops. pthread_create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main here. All threads have finished.\n");
    return 0; // Return success code
}
