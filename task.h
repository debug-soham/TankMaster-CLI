// task.h
#ifndef TASK_H
#define TASK_H

#include <stdlib.h> // For malloc(), free()
#include <string.h> // For snprintf()

// The basic building block for a task
struct Task {
    char description[256];
    int priority;
    struct Task* next; // Pointer to the next task in a list
};

// Use 'Task' instead of 'struct Task'
typedef struct Task Task;

// --- Function Prototypes ---

// Creates a new task node
Task* createTask(const char* description, int priority);

// Adds a task to the end of a list
void addTask(Task** list_head, Task* new_task);

// Prints all tasks in a list
void printTasks(Task* list_head, const char* title);

// Frees all nodes in a list
void freeList(Task** list_head);

#endif // TASK_H
