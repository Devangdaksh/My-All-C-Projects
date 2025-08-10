//
// Simple Zoo Management System in C
// Provides basic management of animals and staff
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANIMALS 100
#define MAX_STAFF 50
#define MAX_LEN 100

#define ANIMAL_FILE "animals.txt"
#define STAFF_FILE "staff.txt"

// Animal Struct
typedef struct {
    char name[MAX_LEN];
    char species[MAX_LEN];
    int age;
} Animal;

// Staff Struct
typedef struct {
    char name[MAX_LEN];
    char role[MAX_LEN];
    int age;
} Staff;

// Global arrays and counts
Animal animals[MAX_ANIMALS];
int animalCount = 0;

Staff staff[MAX_STAFF];
int staffCount = 0;

// Function prototypes
void loadAnimals();
void saveAnimals();
void loadStaff();
void saveStaff();

void addAnimal();
void viewAnimals();
void deleteAnimal();

void addStaff();
void viewStaff();
void deleteStaff();

void showMenu();
int getIntInput();

int main() {
    loadAnimals();
    loadStaff();

    int choice;
    while (1) {
        showMenu();
        printf("Enter your choice: ");
        choice = getIntInput();

        switch(choice) {
            case 1: addAnimal(); break;
            case 2: viewAnimals(); break;
            case 3: deleteAnimal(); break;
            case 4: addStaff(); break;
            case 5: viewStaff(); break;
            case 6: deleteStaff(); break;
            case 7:
                saveAnimals();
                saveStaff();
                printf("Exiting system. Data saved.\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

void showMenu() {
    printf("\n==== Zoo Management System ====\n");
    printf("1. Add Animal\n");
    printf("2. View Animals\n");
    printf("3. Delete Animal\n");
    printf("4. Add Staff\n");
    printf("5. View Staff\n");
    printf("6. Delete Staff\n");
    printf("7. Exit\n");
}

int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input, please enter a number: ");
        while (getchar() != '\n'); // clear buffer
    }
    while (getchar() != '\n'); // clear extra input
    return num;
}

// Animal functions

void loadAnimals() {
    FILE *f = fopen(ANIMAL_FILE, "r");
    if (!f) return; // file doesn't exist yet

    while (fscanf(f, "%99[^,],%99[^,],%d\n", animals[animalCount].name,
                  animals[animalCount].species, &animals[animalCount].age) == 3) {
        animalCount++;
        if (animalCount >= MAX_ANIMALS) break;
    }
    fclose(f);
}

void saveAnimals() {
    FILE *f = fopen(ANIMAL_FILE, "w");
    if (!f) {
        printf("Error saving animals data.\n");
        return;
    }
    for (int i = 0; i < animalCount; i++) {
        fprintf(f, "%s,%s,%d\n", animals[i].name, animals[i].species, animals[i].age);
    }
    fclose(f);
}

void addAnimal() {
    if (animalCount >= MAX_ANIMALS) {
        printf("Animal list is full.\n");
        return;
    }
    printf("Enter animal name: ");
    fgets(animals[animalCount].name, MAX_LEN, stdin);
    animals[animalCount].name[strcspn(animals[animalCount].name, "\n")] = '\0';

    printf("Enter species: ");
    fgets(animals[animalCount].species, MAX_LEN, stdin);
    animals[animalCount].species[strcspn(animals[animalCount].species, "\n")] = '\0';

    printf("Enter age: ");
    animals[animalCount].age = getIntInput();

    animalCount++;
    printf("Animal added successfully.\n");
    saveAnimals();
}

void viewAnimals() {
    if (animalCount == 0) {
        printf("No animals in the zoo.\n");
        return;
    }
    printf("\nAnimals in the Zoo:\n");
    for (int i = 0; i < animalCount; i++) {
        printf("%d. %s (Species: %s, Age: %d)\n", i + 1, animals[i].name, animals[i].species, animals[i].age);
    }
}

void deleteAnimal() {
    if (animalCount == 0) {
        printf("No animals to delete.\n");
        return;
    }
    viewAnimals();
    printf("Enter the number of the animal to delete: ");
    int index = getIntInput();
    if (index < 1 || index > animalCount) {
        printf("Invalid animal number.\n");
        return;
    }

    for (int i = index - 1; i < animalCount - 1; i++) {
        animals[i] = animals[i + 1];
    }
    animalCount--;
    printf("Animal deleted successfully.\n");
    saveAnimals();
}

// Staff functions

void loadStaff() {
    FILE *f = fopen(STAFF_FILE, "r");
    if (!f) return; // file doesn't exist yet

    while (fscanf(f, "%99[^,],%99[^,],%d\n", staff[staffCount].name,
                  staff[staffCount].role, &staff[staffCount].age) == 3) {
        staffCount++;
        if (staffCount >= MAX_STAFF) break;
    }
    fclose(f);
}

void saveStaff() {
    FILE *f = fopen(STAFF_FILE, "w");
    if (!f) {
        printf("Error saving staff data.\n");
        return;
    }
    for (int i = 0; i < staffCount; i++) {
        fprintf(f, "%s,%s,%d\n", staff[i].name, staff[i].role, staff[i].age);
    }
    fclose(f);
}

void addStaff() {
    if (staffCount >= MAX_STAFF) {
        printf("Staff list is full.\n");
        return;
    }
    printf("Enter staff name: ");
    fgets(staff[staffCount].name, MAX_LEN, stdin);
    staff[staffCount].name[strcspn(staff[staffCount].name, "\n")] = '\0';

    printf("Enter role: ");
    fgets(staff[staffCount].role, MAX_LEN, stdin);
    staff[staffCount].role[strcspn(staff[staffCount].role, "\n")] = '\0';

    printf("Enter age: ");
    staff[staffCount].age = getIntInput();

    staffCount++;
    printf("Staff member added successfully.\n");
    saveStaff();
}

void viewStaff() {
    if (staffCount == 0) {
        printf("No staff added yet.\n");
        return;
    }
    printf("\nZoo Staff:\n");
    for (int i = 0; i < staffCount; i++) {
        printf("%d. %s (Role: %s, Age: %d)\n", i + 1, staff[i].name, staff[i].role, staff[i].age);
    }
}

void deleteStaff() {
    if (staffCount == 0) {
        printf("No staff to delete.\n");
        return;
    }
    viewStaff();
    printf("Enter the number of the staff member to delete: ");
    int index = getIntInput();
    if (index < 1 || index > staffCount) {
        printf("Invalid staff number.\n");
        return;
    }

    for (int i = index - 1; i < staffCount - 1; i++) {
        staff[i] = staff[i + 1];
    }
    staffCount--;
    printf("Staff member deleted successfully.\n");
    saveStaff();
}
