#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

#define BUFFER_SIZE 1048576 // Set buffer size to 1 MB for file reading
#define MEMORY_SIZE ((size_t)4 * 1024 * 1024 * 1024) // Allocate 4 GB of memory

// Function prototypes
int contains_confidential(const char *filename, void *memory);
void set_cpu_affinity(int core_id);
int get_number_of_logical_processors(void);
void scan_directory(const char *directory_path, void *memory, int *files_processed, int total_files);
int count_files_in_directory(const char *directory_path);

// Define a structure for thread parameters
typedef struct {
    const char *directory_path; // Path of the directory to scan
    void *memory;               // Memory buffer for file reading
    int *files_processed;       // Pointer to track number of processed files
    int total_files;           // Total number of files to scan
} ThreadData;

// Thread function to scan a directory
DWORD WINAPI scan_directory_thread(LPVOID param) {
    ThreadData *data = (ThreadData *)param;

    // Print a message when the thread starts scanning a subdirectory
    printf("Thread started for directory: %s\n", data->directory_path);

    // Scan the directory using the provided parameters
    scan_directory(data->directory_path, data->memory, data->files_processed, data->total_files);
    
    // Print a message when the thread finishes scanning
    printf("Thread finished for directory: %s\n", data->directory_path);
    
    // Free the duplicated directory path and the ThreadData structure
    free((void *)data->directory_path);
    free(data);
    return 0;
}

// Function to check if a file contains the word "confidential"
int contains_confidential(const char *filename, void *memory) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (!file) {
        perror("Could not open file"); // Print error if the file cannot be opened
        return 0; // Return 0 if file cannot be opened
    }

    char *buffer = (char *)memory; // Use the allocated memory for reading
    size_t bytesRead = 0;

    // Read the file into the allocated memory
    while (fgets(buffer + bytesRead, BUFFER_SIZE, file) != NULL) {
        // Check if the line contains the word "confidential"
        if (strstr(buffer + bytesRead, "confidential") != NULL) {
            fclose(file); // Close the file before returning
            return 1; // Found the word, return 1
        }
        bytesRead += strlen(buffer + bytesRead); // Update bytes read
    }

    fclose(file); // Close the file after reading
    return 0; // Did not find the word, return 0
}

// Function to set the CPU affinity to a specific core
void set_cpu_affinity(int core_id) {
    HANDLE process = GetCurrentProcess(); // Get the current process handle
    DWORD_PTR mask = 1 << core_id; // Create a bitmask for the specified core
    // Set the CPU affinity for the current process
    if (SetProcessAffinityMask(process, mask) == 0) {
        perror("SetProcessAffinityMask failed"); // Print error if setting affinity fails
        exit(EXIT_FAILURE); // Exit if setting affinity fails
    }
}

// Function to get the number of logical processors available
int get_number_of_logical_processors() {
    SYSTEM_INFO sysInfo; // Structure to hold system information
    GetSystemInfo(&sysInfo); // Get system information
    return sysInfo.dwNumberOfProcessors; // Return the number of logical processors
}

// Function to count the total number of files in a directory
int count_files_in_directory(const char *directory_path) {
    DIR *dir = opendir(directory_path); // Open the specified directory
    if (dir == NULL) {
        perror("Could not open directory"); // Print error if directory cannot be opened
        return 0; // Return 0 if directory cannot be opened
    }

    int count = 0; // Initialize file count
    struct dirent *entry; // Structure for directory entries
    struct stat fileStat; // Structure for file status information

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filepath[1024]; // Buffer to hold the full file path
        snprintf(filepath, sizeof(filepath), "%s/%s", directory_path, entry->d_name); // Construct the full path

        if (stat(filepath, &fileStat) == 0) { // Get file status
            if (S_ISREG(fileStat.st_mode)) { // Check if it's a regular file
                count++; // Increment count for regular files
            } else if (S_ISDIR(fileStat.st_mode)) { // Check if it's a directory
                count += count_files_in_directory(filepath); // Recursively count files in subdirectory
            }
        }
    }

    closedir(dir); // Close the directory after reading
    return count; // Return the total file count
}

// Recursive function to scan a directory and its subdirectories
void scan_directory(const char *directory_path, void *memory, int *files_processed, int total_files) {
    DIR *dir = opendir(directory_path); // Open the specified directory for reading
    if (dir == NULL) {
        perror("Could not open directory"); // Print error if directory cannot be opened
        return; // Exit the function if the directory cannot be opened
    }

    struct dirent *entry; // Structure for directory entries
    struct stat fileStat; // Structure for file status information
    HANDLE threads[1024]; // Array to hold thread handles for concurrent directory scans
    int thread_count = 0; // Count of active threads

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip the '.' and '..' entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip these entries
        }

        // Construct the full path of the file or directory
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", directory_path, entry->d_name);

        // Use stat to check if the entry is a regular file or a directory
        if (stat(filepath, &fileStat) == 0) {
            if (S_ISREG(fileStat.st_mode)) { // If it's a regular file
                // Check if the file contains the word "confidential"
                if (contains_confidential(filepath, memory)) {
                    printf("The word 'confidential' was found in: %s\n", filepath); // Print file path if found
                }
                (*files_processed)++; // Increment processed file count
            } else if (S_ISDIR(fileStat.st_mode)) { // If it's a directory
                // Prepare data for the new thread
                ThreadData *data = malloc(sizeof(ThreadData));
                data->directory_path = _strdup(filepath); // Duplicate string for thread use
                data->memory = memory; // Pass the allocated memory buffer
                data->files_processed = files_processed; // Pass the pointer to processed files count
                data->total_files = total_files; // Pass the total file count

                // Print a message when a thread is created
                printf("Creating thread to scan directory: %s\n", filepath);

                // Create a new thread to scan the subdirectory
                threads[thread_count++] = CreateThread(NULL, 0, scan_directory_thread, data, 0, NULL);
            }
        }

        // Print progress bar with dots
        if (total_files > 0) {
            int progress = (int)((*files_processed * 100.0) / total_files); // Calculate progress percentage
            printf("\rProgress: ["); // Start progress bar
            int dots = progress / 2; // Use 2% per dot
            for (int i = 0; i < 50; i++) {
                if (i < dots) {
                    printf("."); // Print dots for progress
                } else {
                    printf(" "); // Print spaces for remaining
                }
            }
            printf("] %d%% ", progress); // Display percentage
            fflush(stdout); // Force output to display immediately
        }
    }

    closedir(dir); // Close the directory after reading

    // Wait for all threads to finish
    WaitForMultipleObjects(thread_count, threads, TRUE, INFINITE);
}

int main(int argc, char *argv[]) {
    const char *directory_path; // Variable to store the directory path
    int core_id; // Variable to store the CPU core ID

    // Check if the correct number of arguments is provided
    if (argc == 2) {
        directory_path = argv[1]; // Get the directory path from command-line arguments
        core_id = rand() % get_number_of_logical_processors(); // Randomly select a core ID
    } else {
        // Print usage instructions if the arguments are incorrect
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE; // Exit with failure
    }

    // Allocate 4 GB of memory
    void *memory = malloc(MEMORY_SIZE);
    if (memory == NULL) {
        perror("Failed to allocate memory"); // Print error if allocation fails
        return EXIT_FAILURE; // Exit with failure
    }

    // Print the amount of memory allocated
    printf("Allocated %zu bytes of memory.\n", MEMORY_SIZE);

    // Set the CPU affinity to the specified core
    set_cpu_affinity(core_id);
    printf("CPU core assigned to program: %d\n", core_id); // Print the core ID

    // Count total files to process
    int total_files = count_files_in_directory(directory_path);
    printf("Total files to scan: %d\n", total_files);
    
    int files_processed = 0; // Keep track of processed files

    // Start timing the execution
    clock_t start_time = clock();

    // Start scanning the specified directory and its subdirectories
    scan_directory(directory_path, memory, &files_processed, total_files);

    // End timing
    clock_t end_time = clock(); // Get the end time
    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nTotal time taken: %.2f seconds\n", elapsed_time); // Print the elapsed time

    // Free allocated memory
    free(memory);

    return EXIT_SUCCESS; // Exit with success
}
