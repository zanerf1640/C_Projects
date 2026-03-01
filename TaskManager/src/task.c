/*
This is the file that perfoms all the different tasks related to the task manager. 
Some of the functions of this program are listed below
    - Create task list
    - clear/reset the task list
    - Add a new task
    - Display all the tasks
    - Mark the tasks as complete or incomplete
    - Delete a specified tasks
    - Search for a specific task
    - Sort the tasks by priority
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/task.h"

// Function to initialize the task list
TaskList* task_list_create(void) {
    // Initialize heap
    TaskList *task = (TaskList*) malloc(sizeof(TaskList));
    // Safety check for memory allocation
    if (task == NULL) {
        fprintf(stderr, "Error, memory allocation failed\n");
        return NULL;
    }
    // Initialize ptr and variables in TaskList
    task->tasks = (Task*) malloc(sizeof(Task) * MAX_TASKS);
    if (task->tasks == NULL) {
        fprintf(stderr, "Error, task array allocation failed\n");
        free(task);
        return NULL;
    }
    task->count = 0;
    task->capacity = MAX_TASKS;

    return task;
}

// Function to clean up the task list
void task_list_destroy(TaskList *list) {
    free(list->tasks);
    list->tasks = NULL;
    free(list);
    list = NULL;
}

// Function to add a task
void task_add(TaskList *list, const char *name, const char *desc, time_t due_date, Priority priority) {
    // input guard
    if (name == NULL) {
        fprintf(stderr, "Error, name is empty\n");
        return;
    }
    if (desc == NULL) {
        fprintf(stderr, "Error, desc is empty\n");
        return;
    }
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return;
    }
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, there are no task\n");
        return;
    }
    // Conditional for capacity
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Task* temp_task = (Task*) realloc(list->tasks, sizeof(Task) * new_capacity);
        if (temp_task == NULL) {
            fprintf(stderr, "Error, invalid tasks\n");
            return;
        }
        // Update tasks and capacity
        list->tasks = temp_task;
        list->capacity = new_capacity;
    }
    // Write new tasks in
    Task* new_task = &list->tasks[list->count];
    new_task->id = list->count + 1;
    new_task->due_date = due_date;
    new_task->priority = priority;
    new_task->completed = 0;
    strncpy(new_task->name, name, MAX_TASK_NAME - 1);
    new_task->name[MAX_TASK_NAME - 1] = '\0';
    strncpy(new_task->description, desc, MAX_TASK_DESC - 1);
    new_task->description[MAX_TASK_DESC - 1] = '\0';
    // increment count
    list->count++;
}

// Helper function to convert Priority enum to string
const char* priority_to_string(Priority p) {
    switch(p) {
        case LOW:
            return "LOW";
        case MEDIUM:
            return "MEDIUM";
        case HIGH:
            return "HIGH";
        default:
            return "UNKNOWN";
    }
}

// Function to display list
void task_list_display(TaskList *list) {
    // Conditional for input
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return;
    }
    // Check if empty
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks to display\n");
        return;
    }
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, there are no task\n");
        return;
    }
    // Print task
    printf("\nID | Name | Priority | Status | Due Date\n");
    for (int i = 0; i < list->count; i++) {
        printf("%d | ", list->tasks[i].id);
        printf("%s | ", list->tasks[i].name);
        printf("%s | ", priority_to_string(list->tasks[i].priority));
        printf("%s | ", list->tasks[i].completed ? "Complete" : "Pending");
        printf("%s", ctime(&list->tasks[i].due_date));
    }
}

// Function to mark task incomplete
void task_mark_complete(TaskList *list, int id) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, there are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Conditional check for ID#
    if (id <= 0) {
        fprintf(stderr, "Invalid id number\n");
        return;
    }
    // Loop through the id
    for (int i = 0; i < list->count; i++) {
        if (id == list->tasks[i].id) {
            if (list->tasks[i].completed == 1) {
                printf("Task already completed\n");
                return;
            } else {
                list->tasks[i].completed = 1;
                printf("Task has been marked as complete!\n");
                return;
            }
        }
    }
    fprintf(stderr, "Error, Task was not found!\n");
    return;
}

// Function to mark task incomplete
void task_mark_incomplete(TaskList *list, int id) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, there are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Conditional check for ID#
    if (id <= 0) {
        fprintf(stderr, "Invalid id number\n");
        return;
    }
    // Loop throught the id
    for (int i = 0; i < list->count; i++) {
        if (id == list->tasks[i].id && list->tasks[i].completed == 1) {
            printf("Task has been marked as incomplete\n");
            list->tasks[i].completed = 0;
            return;
        } else if (id == list->tasks[i].id && list->tasks[i].completed != 1) {
            printf("Task has already been marked as incomplete\n");
            return;
        }
    }
    fprintf(stderr, "Error, Task was not found!\n");
    return;
}

// Function to delete a task
void task_delete(TaskList *list, int id) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, List is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, There are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Conditional check for ID#
    if (id <= 0) {
        fprintf(stderr, "Error, Invalid id number\n");
        return;
    }
    // Loop through to find ID
    for (int i = 0; i < list->count; i++) {
        if (id == list->tasks[i].id) {
            // Loop through from ID -> tail shifting elements
            for (int j = i; j < list->count - 1; j++) {
                list->tasks[j] = list->tasks[j + 1];
            }
            // Update array size
            list->count--;
            return;
        } 
    }
    fprintf(stderr, "Error, Task not found\n");
    return;
}

// Function to serach for a task
void task_search(TaskList *list, const char *keyword) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, List is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, There are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Conditional to check keyword
    if (keyword == NULL) {
        fprintf(stderr, "Error, No keyword\n");
        return;
    }
    int found = 0;
    // Loop through list to find name
    for (int i = 0; i < list->count; i++) {
        // Find the keyword within the name or description
        if (strstr(list->tasks[i].name, keyword) || 
        strstr(list->tasks[i].description, keyword)) {
            printf("ID | Name | Priority | Status | Due Date\n");
            printf("%d | ", list->tasks[i].id);
            printf("%s | ", list->tasks[i].name);
            printf("%s | ", priority_to_string(list->tasks[i].priority));
            printf("%s | ", list->tasks[i].completed ? "Complete" : "Pending");
            printf("%s", ctime(&list->tasks[i].due_date));
            found = 1;
        }
    }
    if (found == 0) {
        printf("No tasks matched\n");
    }
    return;
}

// Function to sort the list by priority (Using bubble sort)
void task_list_sort_by_priority(TaskList *list) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, List is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, There are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Implement bubble sort
    for (int i = 0; i < list->count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->tasks[j].priority < list->tasks[j+1].priority) {
                Task temp_task = list->tasks[j];
                list->tasks[j] = list->tasks[j+1];
                list->tasks[j+1] = temp_task;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
    printf("List successfully sorted!\n");
}

// Function to sort the list by date
void task_list_sort_by_date(TaskList *list) {
    // Check input
    if (list == NULL) {
        fprintf(stderr, "Error, List is empty\n");
        return;
    }
    // Conditional check for tasks 
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, There are no task\n");
        return;
    }
    // Conditional check for tasks count
    if (list->count == 0) {
        fprintf(stderr, "Error, No tasks\n");
        return;
    }
    // Implement bubble sort
    for (int i = 0; i < list->count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->tasks[j].due_date > list->tasks[j+1].due_date) {
                Task temp_task = list->tasks[j];
                list->tasks[j] = list->tasks[j+1];
                list->tasks[j+1] = temp_task;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
    printf("List successfully sorted\n");    
}