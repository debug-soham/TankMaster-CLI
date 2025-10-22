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
        next_task = current->next;
        free(current);
        current = next_task;
    }

    // Set the original head pointer to NULL
    *list_head = NULL;
}

// Pushes a task onto the top of a stack.
void push(Task** stack_top, Task* new_task) {
    if (new_task == NULL) return;

    // 1. Make the new task point to the current top
    new_task->next = *stack_top;
    
    // 2. The new task is now the new top
    *stack_top = new_task;
}


// Deletes a task by its 1-based index.
Task* deleteTaskByIndex(Task** list_head, int index) {
    if (*list_head == NULL || index < 1) {
        return NULL;
    }

    Task* task_to_delete = NULL;

    // Case 1: Deleting the head node
    if (index == 1) {
        task_to_delete = *list_head;
        *list_head = (*list_head)->next;
        task_to_delete->next = NULL;
        return task_to_delete;
    }

    // Case 2: Deleting from middle or end
    Task* current = *list_head;
    int current_index = 1;

    // Traverse to the node *before* the one to delete
    while (current_index < index - 1 && current->next != NULL) {
        current = current->next;
        current_index++;
    }

    // Check if index is valid (i.e., we are at index-1 and next node exists)
    if (current->next != NULL && current_index == index - 1) {
        task_to_delete = current->next;
        current->next = task_to_delete->next;
        task_to_delete->next = NULL;
        return task_to_delete;
    }

    return NULL;
}