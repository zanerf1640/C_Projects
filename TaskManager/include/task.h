#ifndef TASK_H
#define TASK_H

#include <time.h>

#define MAX_TASK_NAME 100
#define MAX_TASK_DESC 500
#define MAX_TASKS 1000

typedef enum {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
} Priority;

typedef struct {
    int id;
    char name[MAX_TASK_NAME];
    char description[MAX_TASK_DESC];
    time_t due_date;
    Priority priority;
    int completed;
} Task;

typedef struct {
    Task *tasks;
    int count;
    int capacity;
} TaskList;

// Function declarations
TaskList* task_list_create(void);
void task_list_destroy(TaskList *list);
void task_add(TaskList *list, const char *name, const char *desc, time_t due_date, Priority priority);
void task_list_display(TaskList *list);
void task_mark_complete(TaskList *list, int id);
void task_mark_incomplete(TaskList *list, int id);
void task_delete(TaskList *list, int id);
void task_search(TaskList *list, const char *keyword);
void task_list_sort_by_priority(TaskList *list);
void task_list_sort_by_date(TaskList *list);

#endif
