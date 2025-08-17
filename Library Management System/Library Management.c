//
// Simple Library Management System in C
// Manages books: add, view, delete records (persistent file storage)
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_LEN 100
#define FILE_NAME "library_books.txt"

// Structure to hold book data
typedef struct {
    char title[MAX_LEN];
    char author[MAX_LEN];
    char isbn[20];
    int quantity;
} Book;

// Global array and counter
Book books[MAX_BOOKS];
int bookCount = 0;

// Function Prototypes
void loadBooks();
void saveBooks();
void addBook();
void viewBooks();
void deleteBook();
void showMenu();
int getIntInput();

int main() {
    // Load stored records when program starts
    loadBooks();

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        int choice = getIntInput();

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                saveBooks();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Menu display
void showMenu() {
    printf("\n===== Library Management System =====\n");
    printf("1. Add Book\n");
    printf("2. View Books\n");
    printf("3. Delete Book\n");
    printf("4. Save and Exit\n");
}

// Load books from file
void loadBooks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No existing library records found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%99[^,],%99[^,],%19[^,],%d\n",
                  books[bookCount].title,
                  books[bookCount].author,
                  books[bookCount].isbn,
                  &books[bookCount].quantity) == 4) {
        bookCount++;
        if (bookCount >= MAX_BOOKS)
            break;
    }
    fclose(file);
    printf("%d book records loaded.\n", bookCount);
}

// Save books to file
void saveBooks() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%s,%d\n",
                books[i].title,
                books[i].author,
                books[i].isbn,
                books[i].quantity);
    }
    fclose(file);
}

// Add a book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    printf("Enter book title: ");
    fgets(books[bookCount].title, MAX_LEN, stdin);
    books[bookCount].title[strcspn(books[bookCount].title, "\n")] = '\0';

    printf("Enter author name: ");
    fgets(books[bookCount].author, MAX_LEN, stdin);
    books[bookCount].author[strcspn(books[bookCount].author, "\n")] = '\0';

    printf("Enter ISBN: ");
    fgets(books[bookCount].isbn, 20, stdin);
    books[bookCount].isbn[strcspn(books[bookCount].isbn, "\n")] = '\0';

    printf("Enter quantity: ");
    books[bookCount].quantity = getIntInput();

    bookCount++;
    printf("Book added successfully!\n");
}

// View all books
void viewBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nList of Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d. Title: %s | Author: %s | ISBN: %s | Quantity: %d\n",
               i + 1,
               books[i].title,
               books[i].author,
               books[i].isbn,
               books[i].quantity);
    }
}

// Delete a book by number
void deleteBook() {
    if (bookCount == 0) {
        printf("No books to delete.\n");
        return;
    }
    viewBooks();

    printf("Enter book number to delete: ");
    int index = getIntInput();

    if (index < 1 || index > bookCount) {
        printf("Invalid book number.\n");
        return;
    }

    for (int i = index - 1; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    printf("Book deleted successfully.\n");
}

// Safe integer input
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    while (getchar() != '\n'); // Clear newline
    return num;
}
