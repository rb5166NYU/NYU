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
/* allows command line arguments to be taken in */
int main(int argc, char* argv[])
{
/* 
- Creates an array "pthread_t" to hold the number specified by "NUMBER_OF_THREADS" 
- Declares status as a integer variable and to check the return value of pthreads_create, and "i" for the loop iteration
*/
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
/* 
- Sets up the loop iteration
- i = 0 is starting point of loop
- i < NUMBER_OF_THREADS is condition checked before each loop is ran
- i++ will increase i by 1 each time this is ran

*/
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        printf("Main here. Creating thread %d\n", i);
        
        // Allocate memory for thread id
    /* 
- malloc is for the memory allocation
- sizeof(int) returns size of bytes as an integer, ensures the correct amount of memory is allocated for storing integers
- if (tid == NULL) will check if the malloc allocation was successful
- perror will print the last error to occur. With the message it will display
- exit terminates program and EXIT_FALIURE mean program terminated with error.
- the combonation of the exits in the code will terminate program with the error code
    */
        int *tid = malloc(sizeof(int));
        if (tid == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
/* This is setting the tid pointer to access the memory location where the integer value for i is stored */
        *tid = i; // Set the thread id
/* 
- pthread_create: This is a POSIX thread library function used to create a new thread.
- &threads[i]: This is a pointer to the pthread_t variable where the thread identifier will be stored. The pthread_t type is used to refer to the thread in the system.
- NULL: This argument is for thread attributes. NULL indicates that the default attributes are used for the new thread.
- print_hello_world: This is the function that the new thread will execute. It must match the signature void *(*start_routine)(void *), which means it takes a void* argument and returns a void*.
- tid: This is the argument passed to the print_hello_world function. It is a pointer to the integer value that represents the thread identifier.
*/
        status = pthread_create(&threads[i], NULL, print_hello_world, tid);
/*
- "status" This variable stores the return value of the "pthread_create" function.
- pthread_create Return Value: The pthread_create function returns 0 on success. If it fails, it returns a non-zero error code indicating the type of error that occurred.
- status != 0: This condition checks if pthread_create returned an error code. If status is not zero, it means that an error occurred during thread creation.
*/
        if (status != 0) {
            printf("Oops. pthread_create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
/* The "pthread_join" function ensures that the main thread waits for each created thread to complete its execution. Without this, the main program could finish and exit before the threads have had a chance to complete their tasks. */
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main here. All threads have finished.\n");
    return 0; // Return success code
}
