Notes for C programing:

### Project Ideas ###
- Create a program that will scan headers and footers for classification markings and print locations of those files with their names
- Scan for files that are or contain images but REALLY fast and will pick up hidden ones
- if files is outside of specified directory preform a deadlock or something like that
- Set these up to be interactive or real time
- follow readers and writers problem from 3 - 8.10.... Program read meta data for classification label, check user account permission and then either allow or don't allow

- *** Optimize hardware to prioritiez the scanning of metadata for things like classifications etc...***
For this all data within a fold/directory/drive will be scanned for key terms. This will be intended for large sets of data and speed. The program will consume processors and memory for fast scanning. Regardless of size.

Papers to reference:

SmartScan: Efficient Metadata Crawl for Storage Management Metadata Querying in Large File Systems
https://www.researchgate.net/profile/Yongwei-Wu/publication/265538826_SmartScan_Efficient_Metadata_Crawl_for_Storage_Management_Metadata_Querying_in_Large_File_Systems/links/54d2c0da0cf2501791806b6f/SmartScan-Efficient-Metadata-Crawl-for-Storage-Management-Metadata-Querying-in-Large-File-Systems.pdf

Document categorization in legal electronic discovery: computer classification vs. manual review
https://asistdl.onlinelibrary.wiley.com/doi/abs/10.1002/asi.21233

Knowledge_Discovery_Enhancing_Data_Mining_and_Decision_Support_Integration-libre.pdf
https://d1wqtxts1xzle7.cloudfront.net/4249279/Knowledge_Discovery_Enhancing_Data_Mining_and_Decision_Support_Integration-libre.pdf?1390836613=&response-content-disposition=inline%3B+filename%3DKnowledge_Discovery_Enhancing_Data_Minin.pdf&Expires=1727314002&Signature=WTdV3jID5fFcJjjd5GvCSv10khnv8SKzCBNwHldi3u8Knc-fzJsucw~D6l57BAEHRf~vVM85D1-kvGLM5kHztzZ9QM1N02HmB2V1xVcWfjeWTD7c28ErzU-aleEp4Uza3UirBvlmBsAqeJ5bR1IsGF3kl9-sGr3yYyoJY6nrHy-oMLJ07dMMDFE6jdKZr2IOv3IibXS-~oJSl28mzij-2qZV-ew216ji1Qg84fl8ony7AfmIunnAa~lqb33-WAOWhRickH8-XTNgNQT4u5L7CQVW7sF833jmIHRHEreRllxt3uyK7TJNPYnDhteYGE8V6ZSxTLpcRo7qUngWNifOqA__&Key-Pair-Id=APKAJLOHF5GGSLRBV4ZA - ////Maybe////

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

struct =  Structures (also called structs) are a way to group several related variables into one place. Each variable in the structure is known as a member of the structure. Unlike an array, a structure can contain many different data types (int, float, char, etc.).

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
### Memory ###

Parkinson’s Law: Programs expand to fill the memory available to hold them.

Memory managment algorithms:
First Fit - The first space a program can fit, will run through memory and allocate the first spot avalible
Next Fit - The next possible spot a program can fit starting from the most recent spot a program was placed
Best Fit - Will look for the smallest possible space a program will fit
Worst Fit - Looks for the space that allows the largest possible space for the program
Quick Fit - rapid search for a space that a program can fit

Virtual memory:
- There is a need to run programs that are too large to fit in memory.
- Solution adopted in the 1960s split programs into little pieces called overlays (Kept on the disk,  swapped in and out of memory
- Virtual memory: each program has its own address space, broken up into chunks called pages

- MMU manages paging, each page file is 4kb
- The relation between virtual addresses and physical memory addresses is given by the page table. Every page begins on a multiple of 4096 and ends 4095 addresses higher, so 4K–8K really means 4096–8191 and 8K to 12K means 8192–12287

- For paging, mapping from virtual to physical must be fast. If the virtual address space is large, the page table will be large.
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
