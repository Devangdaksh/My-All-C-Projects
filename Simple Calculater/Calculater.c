//
// Simple Calculator in C
// Allows: Add, Subtract, Multiply, Divide, Exit
//

#include <stdio.h>

// Function prototypes
void showMenu();
void performAddition();
void performSubtraction();
void performMultiplication();
void performDivision();
int getIntInput();

int main() {
    int choice;

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: performAddition(); break;
            case 2: performSubtraction(); break;
            case 3: performMultiplication(); break;
            case 4: performDivision(); break;
            case 5:
                printf("Exiting Calculator. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Prints the calculator menu
void showMenu() {
    printf("\n=== Simple Calculator Menu ===\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Exit\n");
}

// Safely reads an integer value from user
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    while (getchar() != '\n'); // Discard remaining input
    return num;
}

// Each function below does one operation

void performAddition() {
    int a, b;
    printf("Enter first number: ");
    a = getIntInput();
    printf("Enter second number: ");
    b = getIntInput();
    printf("Result: %d + %d = %d\n", a, b, a + b);
}

void performSubtraction() {
    int a, b;
    printf("Enter first number: ");
    a = getIntInput();
    printf("Enter second number: ");
    b = getIntInput();
    printf("Result: %d - %d = %d\n", a, b, a - b);
}

void performMultiplication() {
    int a, b;
    printf("Enter first number: ");
    a = getIntInput();
    printf("Enter second number: ");
    b = getIntInput();
    printf("Result: %d * %d = %d\n", a, b, a * b);
}

void performDivision() {
    int a, b;
    printf("Enter numerator: ");
    a = getIntInput();
    printf("Enter denominator: ");
    b = getIntInput();
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return;
    }
    double result = (double)a / b;
    printf("Result: %d / %d = %.2f\n", a, b, result);
}
