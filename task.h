// task.h
#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <string.h>

// The basic building block for a task
struct Task {
    char description[256];
    int priority;
    struct Task* next;
};

// Use 'Task' instead of 'struct Task'
typedef struct Task Task;

// --- Function Prototypes ---

// Creates a new task node
Task* createTask(const char* description, int priority);

// Deletes a task by its index
Task* deleteTaskByIndex(Task** list_head, int index);

// Adds a task to the end of a list
void addTask(Task** list_head, Task* new_task);

// Prints all tasks in a list
void printTasks(Task* list_head, const char* title);

// Pushes a task onto the top of a stack
void push(Task** stack_top, Task* new_task);

// Frees all nodes in a list
void freeList(Task** list_head);

// Saves a given linked list to a file.
void saveTasks(Task* list_head, const char* filename);

// Loads tasks from a file into a given list.
void loadTasks(Task** list_head, const char* filename);

#endif // TASK_H
