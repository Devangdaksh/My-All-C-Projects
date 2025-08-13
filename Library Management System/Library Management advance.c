//
// Library Management System with Borrow/Return
// Created by Assistant
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50
#define MAX_LEN 100

#define BOOK_FILE "library_books.txt"
#define MEMBER_FILE "library_members.txt"
#define BORROW_FILE "library_borrows.txt"

// Book structure
typedef struct {
    char title[MAX_LEN];
    char author[MAX_LEN];
    char isbn[20];
    int quantity;
} Book;

// Member structure
typedef struct {
    char name[MAX_LEN];
    int id; // unique student/person ID
} Member;

// Borrow record structure
typedef struct {
    int memberId;
    char isbn[20];
} BorrowRecord;

// Data arrays
Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
BorrowRecord borrows[MAX_BOOKS]; // as many borrow records as books, for simplicity

// Counters
int bookCount = 0;
int memberCount = 0;
int borrowCount = 0;

// Function prototypes
void loadBooks();
void saveBooks();
void loadMembers();
void saveMembers();
void loadBorrows();
void saveBorrows();

void addBook();
void viewBooks();
void deleteBook();

void addMember();
void viewMembers();

void borrowBook();
void returnBook();

int getIntInput();

// ---------------- Main ----------------
int main() {
    loadBooks();
    loadMembers();
    loadBorrows();

    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Delete Book\n");
        printf("4. Add Member\n");
        printf("5. View Members\n");
        printf("6. Borrow Book\n");
        printf("7. Return Book\n");
        printf("8. Save & Exit\n");

        printf("Enter your choice: ");
        int choice = getIntInput();

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: deleteBook(); break;
            case 4: addMember(); break;
            case 5: viewMembers(); break;
            case 6: borrowBook(); break;
            case 7: returnBook(); break;
            case 8:
                saveBooks();
                saveMembers();
                saveBorrows();
                printf("All data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

// ---------------- File Operations ----------------

void loadBooks() {
    FILE *file = fopen(BOOK_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%99[^,],%99[^,],%19[^,],%d\n",
                  books[bookCount].title,
                  books[bookCount].author,
                  books[bookCount].isbn,
                  &books[bookCount].quantity) == 4) {
        bookCount++;
        if (bookCount >= MAX_BOOKS) break;
    }
    fclose(file);
}

void saveBooks() {
    FILE *file = fopen(BOOK_FILE, "w");
    if (!file) return;
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s,%s,%s,%d\n",
                books[i].title, books[i].author, books[i].isbn, books[i].quantity);
    }
    fclose(file);
}

void loadMembers() {
    FILE *file = fopen(MEMBER_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%99[^\n]\n", &members[memberCount].id, members[memberCount].name) == 2) {
        memberCount++;
        if (memberCount >= MAX_MEMBERS) break;
    }
    fclose(file);
}

void saveMembers() {
    FILE *file = fopen(MEMBER_FILE, "w");
    if (!file) return;
    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%d,%s\n", members[i].id, members[i].name);
    }
    fclose(file);
}

void loadBorrows() {
    FILE *file = fopen(BORROW_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%19[^\n]\n", &borrows[borrowCount].memberId, borrows[borrowCount].isbn) == 2) {
        borrowCount++;
    }
    fclose(file);
}

void saveBorrows() {
    FILE *file = fopen(BORROW_FILE, "w");
    if (!file) return;
    for (int i = 0; i < borrowCount; i++) {
        fprintf(file, "%d,%s\n", borrows[i].memberId, borrows[i].isbn);
    }
    fclose(file);
}

// ---------------- Book Functions ----------------

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    printf("Enter title: ");
    fgets(books[bookCount].title, MAX_LEN, stdin);
    books[bookCount].title[strcspn(books[bookCount].title, "\n")] = '\0';

    printf("Enter author: ");
    fgets(books[bookCount].author, MAX_LEN, stdin);
    books[bookCount].author[strcspn(books[bookCount].author, "\n")] = '\0';

    printf("Enter ISBN: ");
    fgets(books[bookCount].isbn, 20, stdin);
    books[bookCount].isbn[strcspn(books[bookCount].isbn, "\n")] = '\0';

    printf("Enter quantity: ");
    books[bookCount].quantity = getIntInput();

    bookCount++;
    printf("Book added.\n");
}

void viewBooks() {
    if (bookCount == 0) {
        printf("No books in library.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("%d. %s | Author: %s | ISBN: %s | Qty: %d\n",
               i + 1, books[i].title, books[i].author, books[i].isbn, books[i].quantity);
    }
}

void deleteBook() {
    viewBooks();
    printf("Enter book number to delete: ");
    int idx = getIntInput();
    if (idx < 1 || idx > bookCount) {
        printf("Invalid choice.\n");
        return;
    }
    for (int i = idx - 1; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    printf("Book deleted.\n");
}

// ---------------- Member Functions ----------------

void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Member list full!\n");
        return;
    }
    printf("Enter Member ID: ");
    members[memberCount].id = getIntInput();

    printf("Enter name: ");
    fgets(members[memberCount].name, MAX_LEN, stdin);
    members[memberCount].name[strcspn(members[memberCount].name, "\n")] = '\0';

    memberCount++;
    printf("Member added.\n");
}

void viewMembers() {
    if (memberCount == 0) {
        printf("No members.\n");
        return;
    }
    for (int i = 0; i < memberCount; i++) {
        printf("%d. ID: %d | Name: %s\n", i + 1, members[i].id, members[i].name);
    }
}

// ---------------- Borrow/Return ----------------

void borrowBook() {
    if (memberCount == 0) {
        printf("No members registered.\n");
        return;
    }
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    viewMembers();
    printf("Enter Member ID: ");
    int memId = getIntInput();

    viewBooks();
    printf("Enter ISBN of book to borrow: ");
    char isbn[20];
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    // Find book
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].quantity > 0) {
                books[i].quantity--;
                borrows[borrowCount].memberId = memId;
                strcpy(borrows[borrowCount].isbn, isbn);
                borrowCount++;
                printf("Book borrowed.\n");
                return;
            } else {
                printf("Book out of stock.\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void returnBook() {
    printf("Enter Member ID: ");
    int memId = getIntInput();

    printf("Enter ISBN of book to return: ");
    char isbn[20];
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    // Find borrow record
    for (int i = 0; i < borrowCount; i++) {
        if (borrows[i].memberId == memId && strcmp(borrows[i].isbn, isbn) == 0) {
            // Increase book quantity
            for (int j = 0; j < bookCount; j++) {
                if (strcmp(books[j].isbn, isbn) == 0) {
                    books[j].quantity++;
                    break;
                }
            }
            // Remove borrow record
            for (int k = i; k < borrowCount - 1; k++) {
                borrows[k] = borrows[k + 1];
            }
            borrowCount--;
            printf("Book returned.\n");
            return;
        }
    }
    printf("No matching borrow record found.\n");
}

// ---------------- Utility ----------------

int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid number: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return num;
}
