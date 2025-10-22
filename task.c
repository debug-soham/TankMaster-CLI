// task.c
#include "task.h"
#include <stdio.h>

// Creates a new task node
Task* createTask(const char* description, int priority) {
    // 1. Allocate memory for the new task
    Task* newTask = (Task*)malloc(sizeof(Task));

    // 2. Check if allocation was successful
    if (newTask == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    // 3. Initialize the task's data
    snprintf(newTask->description, sizeof(newTask->description), "%s", description);
    newTask->priority = priority;
    newTask->next = NULL;

    return newTask;
}

// Adds a task to the end of a list
void addTask(Task** list_head, Task* new_task) {
    if (new_task == NULL) return;

    // Case 1: The list is empty
    if (*list_head == NULL) {
        *list_head = new_task;
        return;
    }

    // Case 2: List is not empty. Find the last node.
    Task* current = *list_head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Append the new task at the end
    current->next = new_task;
}

//  Prints all tasks in a list
void printTasks(Task* list_head, const char* title) {
    printf("\n--- %s ---\n", title);

    if (list_head == NULL) {
        printf("(No tasks in this list)\n");
        return;
    }

    Task* current = list_head;
    int index = 1;
    while (current != NULL) {
        // Print with index and description
        printf("%d. %s\n", index, current->description);
        current = current->next;
        index++;
    }
}

// Frees all nodes in a list
void freeList(Task** list_head) {
    Task* current = *list_head;
    Task* next_task;

    while (current != NULL) {
        next_task = current->next; // Save the next node
        free(current);             // Free the current node
        current = next_task;       // Move to the next node
    }

    // Set the original head pointer to NULL
    *list_head = NULL;
}
