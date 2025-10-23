// task.h
// This header file defines the public "interface" for the task module.
// It specifies the data structure and the functions that main.c can use.

#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <string.h>

// Represents a single task node in a linked list.
struct Task {
    char description[256];
    int priority;          // 1-High, 2-Medium, 3-Low
    struct Task* next;     // Self-referential pointer for the list
};

typedef struct Task Task;

// --- Function Prototypes ---

// Creates a new task node on the heap.
// Returns a pointer to the new task, or NULL on memory failure.
Task* createTask(const char* description, int priority);

// Removes a task from a list given its 1-based index.
// Returns a pointer to the removed task, or NULL if the index was invalid.
Task* deleteTaskByIndex(Task** list_head, int index);

// Appends a new task to the end of a given list (O(n)).
void addTask(Task** list_head, Task* new_task);

// Prints all tasks in a list with a formatted title.
void printTasks(Task* list_head, const char* title);

// Adds a task to the top of a stack (list head) (O(1)).
void push(Task** stack_top, Task* new_task);

// Deallocates all memory for a given list and sets its head to NULL.
void freeList(Task** list_head);

// Saves all tasks from a list to a specified file, overwriting it.
void saveTasks(Task* list_head, const char* filename);

// Loads tasks from a file and appends them to a list.
void loadTasks(Task** list_head, const char* filename);

#endif // TASK_H'
