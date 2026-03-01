/*
This is the file that perfoms all the different tasks related to the task manager.
Some of the functions of this program are listed below
    - Display the menu
    - Run the UI loop
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/file_io.h"

// Helper function to clear the input buffer
static void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}
// Helper function to trim newline character from strings
static void trim_newline(char *text) {
    size_t length = strlen(text);
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }
}


// Function to display the menu
void display_menu(void) {
    printf("\n===== Welcome to the Task Manager =====\n");
    printf("1. Add a new task\n");
    printf("2. Delete a task\n");
    printf("3. Mark a task as complete\n");
    printf("4. Mark a task as incomplete\n");
    printf("5. Display all tasks\n");
    printf("6. Search for a task\n");
    printf("7. Sort tasks by priority\n");
    printf("8. Sort tasks by due date\n");
    printf("9. Exit\n");
}
// Function to run the UI loop
void run_ui(TaskList *list) {
    // Input guard
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return;
    }
    // Main UI loop
    while (1) {
        display_menu();
        // Get user input
        int choice;
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        if (choice < 1 || choice > 9) {
            fprintf(stderr, "Invalid option. Please enter a number between 1 and 9.\n");
            continue;
        }
        // Handle user input
        switch (choice) {
            // Case for adding a new task
            case 1: {
                char name[MAX_TASK_NAME];
                char desc[MAX_TASK_DESC];
                time_t due_date;
                long long due_date_input;
                int priority_input;
                Priority priority;
                printf("Enter task name: ");
                if (fgets(name, sizeof(name), stdin) == NULL) {
                    fprintf(stderr, "Invalid task name input\n");
                    break;
                }
                trim_newline(name);
                printf("Enter task description: ");
                if (fgets(desc, sizeof(desc), stdin) == NULL) {
                    fprintf(stderr, "Invalid task description input\n");
                    break;
                }
                trim_newline(desc);
                printf("Enter task due date (Unix timestamp): ");
                if (scanf("%lld", &due_date_input) != 1) {
                    fprintf(stderr, "Invalid due date input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                due_date = (time_t) due_date_input;
                printf("Enter task priority (1 for LOW, 2 for MEDIUM, 3 for HIGH): ");
                if (scanf("%d", &priority_input) != 1) {
                    fprintf(stderr, "Invalid priority input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                if (priority_input < 1 || priority_input > 3) {
                    fprintf(stderr, "Invalid priority input\n");
                    break;
                }
                // Cast the integer input to the Priority enum
                priority = (Priority)priority_input;
                task_add(list, name, desc, due_date, priority);
                break;
            }
            // Case for deleting a task
            case 2: {
                int id;
                printf("Enter task ID to delete: ");
                if (scanf("%d", &id) != 1) {
                    fprintf(stderr, "Invalid task ID input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                task_delete(list, id);
                break;
            }
            // Case for marking a task as complete
            case 3: {
                int id;
                printf("Enter task ID to mark as complete: ");
                if (scanf("%d", &id) != 1) {
                    fprintf(stderr, "Invalid task ID input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                task_mark_complete(list, id);
                break;
            }
            // Case for marking a task as incomplete
            case 4: {
                int id;
                printf("Enter task ID to mark as incomplete: ");
                if (scanf("%d", &id) != 1) {
                    fprintf(stderr, "Invalid task ID input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                task_mark_incomplete(list, id);
                break;
            }
            // Case for displaying all tasks
            case 5:
                task_list_display(list);
                break;
            // Case for searching for a task
            case 6: {
                char keyword[MAX_TASK_NAME];
                printf("Enter keyword to search for: ");
                if (fgets(keyword, sizeof(keyword), stdin) == NULL) {
                    fprintf(stderr, "Invalid keyword input\n");
                    break;
                }
                trim_newline(keyword);
                if (keyword[0] == '\0') {
                    fprintf(stderr, "Keyword cannot be empty\n");
                    break;
                }
                task_search(list, keyword);
                break;
            }
            // Case for sorting tasks by priority
            case 7:
                task_list_sort_by_priority(list);
                printf("Tasks sorted by priority\n");
                break;
            // Case for sorting tasks by due date
            case 8:
                task_list_sort_by_date(list);
                printf("Tasks sorted by due date\n");
                break;
            // Case for exiting the program
            case 9:
                printf("Exiting Task Manager. Goodbye!\n");
                return;
        }
    }
}