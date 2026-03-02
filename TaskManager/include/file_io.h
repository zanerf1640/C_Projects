#ifndef FILE_IO_H
#define FILE_IO_H

#include "task.h"

#define DATA_FILE "data/tasks.dat"

// Function declarations
int save_tasks_to_file(TaskList *list, const char *filename);
TaskList* load_tasks_from_file(const char *filename);
void initialize_data_file(void);

#endif
