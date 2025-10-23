// main.c
#include <stdio.h>
#include <string.h>
#include "task.h"

// --- FILENAMES ---
#define FILE_HIGH "tasks_high.dat"
#define FILE_MEDIUM "tasks_medium.dat"
#define FILE_LOW "tasks_low.dat"
#define FILE_COMPLETED "tasks_completed.dat"

// Helper function to safely read a line of text and remove the newline.
void read_line(char* buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0'; 
        clearerr(stdin); 
    }
}

// Helper function to get a simple integer choice. Returns -1 on invalid input.
int get_menu_choice() {
    char buffer[16];
    read_line(buffer, sizeof(buffer));
    int choice;
    if (sscanf(buffer, "%d", &choice) == 1) {
        return choice;
    } else {
        return -1; 
    }
}

// Prints the main menu
void print_menu() {
    printf("\n|============================|\n");
    printf("|       TaskMaster CLI       |\n");
    printf("|============================|\n");
    printf("| 1. Add New Task            |\n");
    printf("| 2. View Current Tasks      |\n");
    printf("| 3. Complete a Task         |\n");
    printf("| 4. View Completed History  |\n");
    printf("| 5. Exit                    |\n");
    printf("|============================|\n");
    printf("\nEnter your choice: ");
}

// Helper function for the "Complete Task" workflow
void complete_task_workflow(Task** high, Task** medium, Task** low, Task** completed_stack) {
    printf("Which priority list to complete from? (1-High, 2-Medium, 3-Low): ");
    int priority_choice = get_menu_choice();

    Task** list_to_modify = NULL; // Pointer to the head pointer

    if (priority_choice == 1)      list_to_modify = high;
    else if (priority_choice == 2) list_to_modify = medium;
    else if (priority_choice == 3) list_to_modify = low;
    else {
        printf("Invalid priority. Returning to menu.\n");
        return;
    }

    if (*list_to_modify == NULL) {
        printf("That list is empty. No tasks to complete.\n");
        return;
    }

    printf("Enter the task number to complete: ");
    int index_choice = get_menu_choice();
    
    if (index_choice < 1) {
        printf("Invalid task number.\n");
        return;
    }

    Task* completed_task = deleteTaskByIndex(list_to_modify, index_choice);

    if (completed_task != NULL) {
        push(completed_stack, completed_task);
        printf("\nTask '%s' completed and moved to history!\n", completed_task->description);
    } else {
        printf("\nInvalid task number. Task not found.\n");
    }
}

int main() {
    // --- SETUP ---
    Task* high_priority = NULL;
    Task* medium_priority = NULL;
    Task* low_priority = NULL;
    Task* completed_tasks_stack = NULL;

    // --- LOAD TASKS ---
    loadTasks(&high_priority, FILE_HIGH);
    loadTasks(&medium_priority, FILE_MEDIUM);
    loadTasks(&low_priority, FILE_LOW);
    loadTasks(&completed_tasks_stack, FILE_COMPLETED);
    
    int running = 1;
    printf("\nWelcome to TaskMaster CLI!\n");

    // --- MAIN APPLICATION LOOP ---
    while (running) {
        // 1. DISPLAY MENU
        print_menu();

        // 2. USER INPUT
        int choice = get_menu_choice();
        switch (choice) {
            case 1: // Add New Task
            {
                char description[256];
                int priority_choice = -1;

                printf("Enter task description: ");
                read_line(description, sizeof(description));

                if (description[0] == '\0') {
                    printf("Task description cannot be empty. Task not added.\n");
                    break;
                }

                printf("Enter priority (1-High, 2-Medium, 3-Low): ");
                priority_choice = get_menu_choice();

                if (priority_choice < 1 || priority_choice > 3) {
                    printf("Invalid priority. Task not added.\n");
                    break;
                }

                Task* newTask = createTask(description, priority_choice);
                if (newTask != NULL) {
                    if (priority_choice == 1)      addTask(&high_priority, newTask);
                    else if (priority_choice == 2) addTask(&medium_priority, newTask);
                    else                           addTask(&low_priority, newTask);
                    
                    printf("\nTask added successfully!\n");
                }
            }
            break;

            case 2: // View Current Tasks
                printf("\n<<<<< CURRENT TASKS >>>>>\n");
                printTasks(high_priority, "HIGH PRIORITY");
                printTasks(medium_priority, "MEDIUM PRIORITY");
                printTasks(low_priority, "LOW PRIORITY");
                break;

            case 3: // Complete a Task
                complete_task_workflow(&high_priority, &medium_priority, &low_priority, &completed_tasks_stack);
                break;

            case 4: // View Completed History=
                printTasks(completed_tasks_stack, "COMPLETED TASKS (Most Recent First)");
                break;

            case 5: // Exit
                running = 0;
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    }

    // --- SAVE & CLEANUP ---
    printf("\nSaving tasks to file...\n");
    saveTasks(high_priority, FILE_HIGH);
    saveTasks(medium_priority, FILE_MEDIUM);
    saveTasks(low_priority, FILE_LOW);
    saveTasks(completed_tasks_stack, FILE_COMPLETED);

    printf("Exiting. Cleaning up all lists...\n");
    freeList(&high_priority);
    freeList(&medium_priority);
    freeList(&low_priority);
    freeList(&completed_tasks_stack);
    printf("Cleanup complete. Goodbye!\n");

    return 0;
}
