//
// To-Do List Program
// Created by Devang on 28-07-2025
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // getcwd() for debug

// ---------------------
// Configuration Macros
// ---------------------
#define MAX_TASKS 100             // Maximum number of tasks allowed
#define MAX_LEN 100               // Maximum characters in a single task description

// IMPORTANT: To ensure CLion finds/saves the file, keep it in project root
#define FILE_NAME "tasks.txt"     // Name of the file used for saving/loading tasks

// ---------------------
// Struct Definition: One Task
// ---------------------
typedef struct {
    char description[MAX_LEN];   // Holds the text for the task
} Task;

// ---------------------
//  Variables
// ---------------------
Task tasks[MAX_TASKS];            // Array to store tasks
int taskCount = 0;                 // Total number of current tasks

// ---------------------
// Function 
// ---------------------
void loadTasks();      // Load existing tasks from file when program starts
void saveTasks();      // Save current tasks to file
void addTask();        // Add a task
void viewTasks();      // Show all tasks
void deleteTask();     // Remove a task
void showMenu();       // Display menu options
int getIntInput();     // Safely get integer input from user

// ---------------------
// Main function
// ---------------------
int main() {
    int choice;

    // Show the program's current working directory 
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current Working Directory: %s\n", cwd);

    // Load tasks from file before starting
    loadTasks();

    // Menu loop
    while (1) {
        showMenu();
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                saveTasks();
                break;
            case 5:
                printf("Exiting and saving tasks...\n");
                saveTasks();
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// ---------------------
// Show Menu Options
// ---------------------
void showMenu() {
    printf("\n===== TO-DO LIST MENU =====\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Delete Task\n");
    printf("4. Save Tasks\n");
    printf("5. Exit\n");
}

// ---------------------
// Load Tasks from File
// ---------------------
void loadTasks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No existing task file found. Starting with an empty list.\n");
        return;
    }

    while (fgets(tasks[taskCount].description, MAX_LEN, file)) {
        // Remove newline character from end
        tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = '\0';
        taskCount++;
        if (taskCount >= MAX_TASKS) break;  // Stop if max limit reached
    }

    fclose(file);
    printf("%d tasks loaded from %s\n", taskCount, FILE_NAME);
}

// ---------------------
// Save Tasks to File
// ---------------------
void saveTasks() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Cannot open %s for writing.\n", FILE_NAME);
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i].description);
    }

    fclose(file);
    printf("Tasks saved successfully to %s.\n", FILE_NAME);
}

// ---------------------
// Add a New Task
// ---------------------
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full! Cannot add more tasks.\n");
        return;
    }

    printf("Enter task description: ");
    fgets(tasks[taskCount].description, MAX_LEN, stdin);
    // Remove trailing newline if present
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = '\0';

    taskCount++;
    printf("Task added successfully!\n");

    saveTasks(); // Auto-save after adding
}

// ---------------------
// View All Tasks
// ---------------------
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks to show.\n");
        return;
    }

    printf("\nYour Tasks:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", i + 1, tasks[i].description);
    }
}

// ---------------------
// Delete a Task
// ---------------------
void deleteTask() {
    if (taskCount == 0) {
        printf("No tasks to delete.\n");
        return;
    }

    viewTasks();
    printf("Enter task number to delete: ");
    int index = getIntInput();

    if (index < 1 || index > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    // Shift tasks to remove gap
    for (int i = index - 1; i < taskCount - 1; i++) {
        strcpy(tasks[i].description, tasks[i + 1].description);
    }

    taskCount--;
    printf("Task deleted successfully.\n");

    saveTasks(); // Auto-save after deleting
}

// ---------------------
// Safe Integer Input
// ---------------------
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n'); // clear input buffer
    }
    while (getchar() != '\n'); // discard leftover input
    return num;
}
