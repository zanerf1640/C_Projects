#include <stdio.h>
#include <stdlib.h>
#include "../include/file_io.h"

// Function to save tasks to file
int save_tasks_to_file(TaskList *list, const char *filename) {
    // Input guard
    if (list == NULL) {
        fprintf(stderr, "Error, list is empty\n");
        return -1;
    }
    if (list->tasks == NULL) {
        fprintf(stderr, "Error, there are no tasks\n");
        return -1;
    }
    if (filename == NULL) {
        fprintf(stderr, "Error, filename is empty\n");
        return -1;
    }
    // Check list count
    if (list->count < 0) {
        fprintf(stderr, "Error, Invalid task count\n");
        return -1;
    }
    // Open file for writing
    FILE *file = fopen(filename, "wb");
    if (file == NULL){
        fprintf(stderr, "Failed to Open File\n");
        return -1;
    }
    // Write task count to file
    if (fwrite(&list->count, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Error writing task count to file %s\n", filename);
        fclose(file);
        return -1;
    }
    // Write tasks to file
    if (fwrite(list->tasks, sizeof(Task), list->count, file) != (size_t)list->count) {
        fprintf(stderr, "Error writing tasks to %s\n", filename);
        fclose(file);
        return -1;
    }
    // Close file 
    fclose(file);
    return 0;
}

// File to load tasks from file
TaskList* load_tasks_from_file(const char *filename) {
    // Input guards
    if (filename == NULL) {
        fprintf(stderr, "Error, filename is empty\n");
        return NULL;
    }
    //Open file for reading
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return task_list_create();
    }
    // Destination list
    TaskList *list = task_list_create();
    if (list == NULL) {
        fprintf(stderr, "Error, Failed to create task list\n");
        fclose(file);
        return NULL;
    }
    // Read task count from file
    int count = 0;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        if (feof(file)) {
            fclose(file);
            return list;
        }
        fprintf(stderr, "Error reading task count from file %s\n", filename);
        fclose(file);
        task_list_destroy(list);
        return NULL;
    }
    // Check count validity
    if (count < 0 || count > MAX_TASKS) {
        fprintf(stderr, "Error, Invalid task count in file %s\n", filename);
        fclose(file);
        task_list_destroy(list);
        return NULL;
    }
    // Read tasks from file
    if (count > 0) {
        if (fread(list->tasks, sizeof(Task), count, file) != (size_t)count) {
            fprintf(stderr, "Error reading tasks from file %s\n", filename);
            fclose(file);
            task_list_destroy(list);
            return NULL;
        }
    }
    // Update list count
    list->count = count;
    // Close file
    fclose(file);
    return list;
}

// Function to initialize data file
void initialize_data_file(void) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        file = fopen(DATA_FILE, "wb");
        if (file == NULL) {
            fprintf(stderr, "Failed to create data file\n");
            return;
        }
    }

    fclose(file);
}