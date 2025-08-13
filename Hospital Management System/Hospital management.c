//
// Hospital Management System in C
// Manages patient records: add, view, delete, save/load
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_LEN 100
#define FILE_NAME "patients.txt"

// Struct to represent a patient
typedef struct {
    char name[MAX_LEN];
    int age;
    char gender[10];
    char diagnosis[MAX_LEN];
} Patient;

// Global array and count
Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Function prototypes
void loadPatients();
void savePatients();
void addPatient();
void viewPatients();
void deletePatient();
void showMenu();
int getIntInput();

int main() {
    loadPatients();

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        int choice = getIntInput();

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                deletePatient();
                break;
            case 4:
                savePatients();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Displays menu options
void showMenu() {
    printf("\n===== Hospital Management System =====\n");
    printf("1. Add Patient Record\n");
    printf("2. View Patient Records\n");
    printf("3. Delete Patient Record\n");
    printf("4. Save and Exit\n");
}

// Loads patients data from file
void loadPatients() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No existing patient records found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%99[^,],%d,%9[^,],%99[^\n]\n",
                  patients[patientCount].name,
                  &patients[patientCount].age,
                  patients[patientCount].gender,
                  patients[patientCount].diagnosis) == 4) {
        patientCount++;
        if (patientCount >= MAX_PATIENTS)
            break;
    }
    fclose(file);
    printf("%d patient records loaded.\n", patientCount);
}

// Saves patients data to file
void savePatients() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }
    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%s,%d,%s,%s\n",
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                patients[i].diagnosis);
    }
    fclose(file);
}

// Adds a patient record
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient list is full! Cannot add more.\n");
        return;
    }

    printf("Enter patient name: ");
    fgets(patients[patientCount].name, MAX_LEN, stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = '\0';

    printf("Enter age: ");
    patients[patientCount].age = getIntInput();

    printf("Enter gender (Male/Female/Other): ");
    fgets(patients[patientCount].gender, 10, stdin);
    patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = '\0';

    printf("Enter diagnosis: ");
    fgets(patients[patientCount].diagnosis, MAX_LEN, stdin);
    patients[patientCount].diagnosis[strcspn(patients[patientCount].diagnosis, "\n")] = '\0';

    patientCount++;
    printf("Patient record added successfully!\n");
}

// Views all patient records
void viewPatients() {
    if (patientCount == 0) {
        printf("No patient records to display.\n");
        return;
    }

    printf("\nList of Patients:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("%d. Name: %s | Age: %d | Gender: %s | Diagnosis: %s\n",
               i + 1, patients[i].name, patients[i].age, patients[i].gender, patients[i].diagnosis);
    }
}

// Deletes a patient record by index
void deletePatient() {
    if (patientCount == 0) {
        printf("No patient records to delete.\n");
        return;
    }

    viewPatients();
    printf("Enter patient number to delete: ");
    int index = getIntInput();

    if (index < 1 || index > patientCount) {
        printf("Invalid patient number.\n");
        return;
    }

    // Shift records to fill the gap
    for (int i = index - 1; i < patientCount - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patientCount--;
    printf("Patient record deleted successfully.\n");
}

// Gets a safe integer input from the user
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a valid number: ");
        while (getchar() != '\n'); // clear input buffer
    }
    while (getchar() != '\n'); // clear newline left in buffer
    return num;
}
