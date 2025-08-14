//
// Factorial Calculator in C
// Calculates n! for a given non-negative integer
// Author: Assistant
//

#include <stdio.h>

// Function prototypes
void showMenu();
unsigned long long factorial(int n);
int getIntInput();

int main() {
    int choice;

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        choice = getIntInput();

        if (choice == 1) {
            printf("Enter a non-negative integer: ");
            int num = getIntInput();

            if (num < 0) {
                printf("Factorial is not defined for negative numbers.\n");
            } else {
                unsigned long long result = factorial(num);
                printf("Factorial of %d is: %llu\n", num, result);
            }
        }
        else if (choice == 2) {
            printf("Exiting the program. Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Show menu options
void showMenu() {
    printf("\n=== Factorial Calculator ===\n");
    printf("1. Calculate Factorial\n");
    printf("2. Exit\n");
}

// Compute factorial using iterative approach
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Safe integer input from user
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n'); // clear input buffer
    }
    while (getchar() != '\n'); // clear newline from buffer
    return num;
}
