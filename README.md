# TaskMaster CLI

TaskMaster CLI is a command-line application for managing to-do items, built as a C project to demonstrate core data structures.

## Features

* **Add Tasks:** Add a new task with a text description.
* **Prioritize:** Assign a High, Medium, or Low priority to each new task.
* **View Tasks:** View all pending tasks, neatly grouped by their priority.
* **Complete Tasks:** Mark a task as complete. It's then removed from the pending list and moved to the history.
* **View History:** View the list of completed tasks. This list is displayed in LIFO (Last-In, First-Out) order.
* **Data Persistence:** All tasks (pending and completed) are automatically saved to `.dat` files on exit and reloaded on the next startup.

## Data Structures

This project uses the following data structures, built from scratch in C:

* **Linked Lists:** Three separate singly linked lists are used to manage the High,Medium, and Low priority task queues.
* **Stack:** A stack (implemented as a linked list) is used to store the history of completed tasks, enabling the LIFO behavior.

## How to Compile and Run

1.  Ensure you have a C compiler (like `gcc`) installed.

2.  Place all three files (`main.c`, `task.c`, `task.h`) in the same directory.

3.  Compile the program from your terminal:
    ```bash
    gcc main.c task.c -o task_manager
    ```

4.  Run the application:
    ```bash
    task_manager
    ```