Notes for C programing:

### Project Ideas ###
- Create a program that will scan headers and footers for classification markings and print locations of those files with their names
- Scan for files that are or contain images but REALLY fast and will pick up hidden ones
- if files is outside of specified directory preform a deadlock or something like that
- Set these up to be interactive or real time
- follow readers and writers problem from 3 - 8.10.... Program read meta data for classification label, check user account permission and then either allow or don't allow
.....  .....  .....  .....  ..... .....  .....  .....  .....  .....
### Guide ###
Sections are separated by ### ###

Website to complie code online: https://www.onlinegdb.com/

Education: https://www.cc4e.com/
- code is 42

In my program descriptions anything with ( ) is a personal side comment, while anyhting within " " is a part of the C programing code
.....  .....  .....  .....  ..... .....  .....  .....  .....  .....
### Notes ### 

You need to add { } if going over 1 statment (what is a statment)
to make a comment /* comment */

float = numbers with a fractional part (decials?)

bursttime = how much time is takes to run the process
example of bursttime being used:
inpcb.total_bursttime
inpcb.remaining_bursttime

struct:
- Structures (also called structs) are a way to group several related variables into one place. Each variable in the structure is known as a member of the structure. Unlike an array, a structure can contain many different data types (int, float, char, etc.).

.....  .....  .....  .....  ..... .....  .....  .....  .....  .....
### Processes and Threads ###
- a process is an application in memory (container for application)
- process states: running, ready, and blocked
- you can have multiple threads per process
- pthread.h header for threads

Pthread_create: Creates new thread
Pthread_exit: Terminates a calling thread
Pthread_join: waits for a specific thread to exit
Pthread_yield: Release CPU to let another thread run
Pthread_attr_init: Creates and initilizes a threads attriubute structure
Pthread_attr_destroy: Remove a threads attribute structure

.....  .....  .....  .....  ..... .....  .....  .....  .....  .....
### What Each Program in this branch will help with ###

isleapyear: 
- will show how to incorperate adding command line arguments into the program. 
- This will also show how to take that commnad line string and convert it into a integer
- Useage of atoi, argc, argv[], char and if/else statments
- usage of boolan && ||

Counted Loop:
- Shows how a loop within C works
- how to increase a number each time a program is ran within a loop
- shows how "for" is used and "++"

Function call by value:
- Shows hwo to assign numbers to values and call those functions later in the code
- will retrevie values
- "return"

Hello:
- The classic hello world
- shows how to have a program print a string of text when ran

Line Input:
- shows how to create an array of characters
- creating limits for that array

Number Guess:
- Shows how to set up a loop based on user input
- will continually run a loop until the number we are looking for is entered
- Will show "EOF" "&" "while" "if" "break" "else if" "%d"

Number Input: 
- Asking for inputs and assigning values based on those inputs

Pick a Number:
- Will ask for a number and then display the number entered
- "return"

Read A File:
- Creates an array and will read a file up to the limit of that array
- Opens a file within its working directory
- "char line[]" "FILE *hand" "fopen" "fgets" "line" "hand" "NULL"

String Inpuut:
- Creates an array 
- prompts the user for an input
- will take the input string, store as variable
- display the string the user entered
- "%100s" <- looks a string (%s) up to 100 characters "scanf" "printf"

CreateThreads:
- Shows how to use the POSIX thread library (The <pthread.h> header)
- "void" "free" "#define" "perror" "malloc" "exit" "pthread_create" "pthread_join" "pthread_t" "pthread_exit"
- Creates threads, gets responses from them, prints the creation and responses from the threads created
