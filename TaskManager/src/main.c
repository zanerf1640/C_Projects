/*
This is the main entry point for the Task Manager application. It initializes the data file, loads existing tasks, starts the user interface, 
and saves tasks before exiting.

To compile: gcc src/*.c -o task_manager
To run: ./task_manager
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"
#include "../include/file_io.h"
#include "../include/ui.h"

int main(void) {
    // Initialize data directory
    initialize_data_file();
    // Load existing tasks from file
    TaskList *list = load_tasks_from_file(DATA_FILE);
    if (list == NULL) {
        fprintf(stderr, "Error, failed to load tasks from file\n");
        return EXIT_FAILURE;
    }
    // Start the UI loop
    run_ui(list);
    // Save tasks before exiting
    if (save_tasks_to_file(list, DATA_FILE) != 0) {
        fprintf(stderr, "Error, failed to save tasks to file\n");
        task_list_destroy(list);
        return EXIT_FAILURE;
    }
    // Clean up task list
    task_list_destroy(list);
    
    return EXIT_SUCCESS;
}
