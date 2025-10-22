// main.c
#include <stdio.h>
#include <string.h>
#include "task.h"

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
    printf("| 4. Exit                    |\n");
    printf("|============================|\n");
    printf("\nEnter your choice: ");
}

int main() {
    // --- SETUP ---
    Task* high_priority = NULL;
    Task* medium_priority = NULL;
    Task* low_priority = NULL;
    
    int running = 1;
    printf("\nWelcome to TaskMaster CLI!\n");

    // --- MAIN APPLICATION LOOP ---
    while (running) {
        // 1. DISPLAY MENU
        print_menu();

        // 2. GET USER INPUT
        int choice = get_menu_choice();

        // 3. PROCESS USER INPUT
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
                printf("This feature will be implemented soon!\n");
                break;

            case 4: // Exit
                running = 0;
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
    }

    // --- CLEANUP ---
    printf("\nExiting. Cleaning up all lists...\n");
    freeList(&high_priority);
    freeList(&medium_priority);
    freeList(&low_priority);
    printf("Cleanup complete. Goodbye!\n");

    return 0;
}
