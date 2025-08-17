//
// Simple Bank Management System in C
// Features: Add/View/Delete Accounts, Deposit, Withdraw, Check Balance
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define NAME_LEN 50
#define ACC_FILE "accounts.txt"

// Structure to store account details
typedef struct {
    int accountNumber;
    char name[NAME_LEN];
    float balance;
} Account;

// Global array and count
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function prototypes
void loadAccounts();
void saveAccounts();
void addAccount();
void viewAccounts();
void deposit();
void withdraw();
void checkBalance();
void deleteAccount();
void showMenu();
int getIntInput();
float getFloatInput();
int findAccountIndex(int accNo);

int main() {
    loadAccounts();

    int choice;
    while (1) {
        showMenu();
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: addAccount(); break;
            case 2: viewAccounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: checkBalance(); break;
            case 6: deleteAccount(); break;
            case 7:
                saveAccounts();
                printf("Data saved. Exiting...\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Display main menu
void showMenu() {
    printf("\n=== Bank Management System ===\n");
    printf("1. Add Account\n");
    printf("2. View Accounts\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Check Balance\n");
    printf("6. Delete Account\n");
    printf("7. Save and Exit\n");
}

// Load account records from file
void loadAccounts() {
    FILE *file = fopen(ACC_FILE, "r");
    if (file == NULL) {
        printf("No previous records found. Starting fresh.\n");
        return;
    }
    while (fscanf(file, "%d,%49[^,],%f\n", &accounts[accountCount].accountNumber, accounts[accountCount].name, &accounts[accountCount].balance) == 3) {
        accountCount++;
        if (accountCount >= MAX_ACCOUNTS) break;
    }
    fclose(file);
    printf("%d accounts loaded.\n", accountCount);
}

// Save all accounts to file
void saveAccounts() {
    FILE *file = fopen(ACC_FILE, "w");
    if (file == NULL) {
        printf("Error saving data.\n");
        return;
    }
    for (int i = 0; i < accountCount; i++)
        fprintf(file, "%d,%s,%.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);

    fclose(file);
}

// Add a new account
void addAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum accounts reached!\n");
        return;
    }
    Account newAccount;

    printf("Enter Account Number: ");
    newAccount.accountNumber = getIntInput();

    if(findAccountIndex(newAccount.accountNumber) != -1){
        printf("Account number already exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    fgets(newAccount.name, NAME_LEN, stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';

    printf("Enter Initial Deposit Amount: ");
    newAccount.balance = getFloatInput();

    accounts[accountCount++] = newAccount;
    printf("Account created successfully!\n");
    saveAccounts();
}

// View all accounts
void viewAccounts() {
    if (accountCount == 0) {
        printf("No accounts to display.\n");
        return;
    }
    printf("\nList of Accounts:\n");
    for (int i = 0; i < accountCount; i++)
        printf("%d. Account Number: %d | Name: %s | Balance: %.2f\n", i + 1, accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
}

// Deposit money into an account
void deposit() {
    printf("Enter Account Number: ");
    int acc = getIntInput();
    int idx = findAccountIndex(acc);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }
    printf("Enter amount to deposit: ");
    float amount = getFloatInput();

    if (amount <= 0) {
        printf("Enter a positive amount!\n");
        return;
    }
    accounts[idx].balance += amount;
    printf("Deposit successful!\n");
    saveAccounts();
}

// Withdraw money from an account
void withdraw() {
    printf("Enter Account Number: ");
    int acc = getIntInput();
    int idx = findAccountIndex(acc);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }
    printf("Enter amount to withdraw: ");
    float amount = getFloatInput();

    if (amount <= 0) {
        printf("Enter a positive amount!\n");
        return;
    }
    if (accounts[idx].balance < amount) {
        printf("Insufficient balance!\n");
        return;
    }
    accounts[idx].balance -= amount;
    printf("Withdrawal successful!\n");
    saveAccounts();
}

// Check balance of an account
void checkBalance() {
    printf("Enter Account Number: ");
    int acc = getIntInput();
    int idx = findAccountIndex(acc);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }
    printf("Current balance for account %d: %.2f\n", accounts[idx].accountNumber, accounts[idx].balance);
}

// Delete an account
void deleteAccount() {
    printf("Enter Account Number to delete: ");
    int acc = getIntInput();
    int idx = findAccountIndex(acc);
    if (idx == -1) {
        printf("Account not found.\n");
        return;
    }
    for (int i = idx; i < accountCount - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    accountCount--;
    printf("Account deleted successfully.\n");
    saveAccounts();
}

// Find index of account by account number
int findAccountIndex(int accNo) {
    for (int i = 0; i < accountCount; i++)
        if (accounts[i].accountNumber == accNo)
            return i;
    return -1;
}

// Safe integer input
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return num;
}

// Safe float input
float getFloatInput() {
    float num;
    while (scanf("%f", &num) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return num;
}
