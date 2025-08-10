//
// Simple Calculator in C (Float Version)
// Supports addition, subtraction, multiplication, division, exit
// Works with decimal values
//

#include <stdio.h>

// Function prototypes
void showMenu();
void performAddition();
void performSubtraction();
void performMultiplication();
void performDivision();
float getFloatInput();
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

// Safely reads a floating-point value from user
float getFloatInput() {
    float num;
    while (scanf("%f", &num) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n'); // clear buffer
    }
    while (getchar() != '\n'); // discard leftover input
    return num;
}

// Safely reads an integer value from user (menu choice)
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n'); // clear buffer
    }
    while (getchar() != '\n');
    return num;
}

// Each function below does one operation with floats

void performAddition() {
    float a, b;
    printf("Enter first number: ");
    a = getFloatInput();
    printf("Enter second number: ");
    b = getFloatInput();
    printf("Result: %.2f + %.2f = %.2f\n", a, b, a + b);
}

void performSubtraction() {
    float a, b;
    printf("Enter first number: ");
    a = getFloatInput();
    printf("Enter second number: ");
    b = getFloatInput();
    printf("Result: %.2f - %.2f = %.2f\n", a, b, a - b);
}

void performMultiplication() {
    float a, b;
    printf("Enter first number: ");
    a = getFloatInput();
    printf("Enter second number: ");
    b = getFloatInput();
    printf("Result: %.2f * %.2f = %.2f\n", a, b, a * b);
}

void performDivision() {
    float a, b;
    printf("Enter numerator: ");
    a = getFloatInput();
    printf("Enter denominator: ");
    b = getFloatInput();
    if (b == 0.0f) {
        printf("Error: Division by zero is not allowed.\n");
        return;
    }
    printf("Result: %.2f / %.2f = %.2f\n", a, b, a / b);
}
