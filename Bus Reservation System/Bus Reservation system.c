// Simple Bus Reservation System in C
// Features: add buses, book tickets, cancel tickets, view buses/bookings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 50
#define MAX_BOOKINGS 200
#define MAX_LEN 100

#define BUS_FILE "buses.txt"
#define BOOKING_FILE "bookings.txt"

// ---------- Structures ----------

typedef struct {
    int busId;
    char route[MAX_LEN];
    char driver[MAX_LEN];
    int totalSeats;
    int availableSeats;
} Bus;

typedef struct {
    int bookingId;
    int busId;
    char passengerName[MAX_LEN];
    int seatsBooked;
} Booking;

// ---------- Global Variables ----------
Bus buses[MAX_BUSES];
int busCount = 0;

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

int nextBookingId = 1; // Automatically assigns booking IDs

// ---------- Function Prototypes ----------
void loadBuses();
void saveBuses();
void loadBookings();
void saveBookings();

void addBus();
void viewBuses();
void bookTicket();
void viewBookings();
void cancelBooking();

int getIntInput();
char *readLine(char *buffer, int size);

// ---------- Main ----------
int main() {
    loadBuses();
    loadBookings();

    int choice;
    while (1) {
        printf("\n===== Bus Reservation System =====\n");
        printf("1. Add Bus\n");
        printf("2. View Buses\n");
        printf("3. Book Ticket\n");
        printf("4. View Bookings\n");
        printf("5. Cancel Booking\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: addBus(); break;
            case 2: viewBuses(); break;
            case 3: bookTicket(); break;
            case 4: viewBookings(); break;
            case 5: cancelBooking(); break;
            case 6:
                saveBuses();
                saveBookings();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// ---------- File Handling ----------
void loadBuses() {
    FILE *file = fopen(BUS_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n",
                  &buses[busCount].busId,
                  buses[busCount].route,
                  buses[busCount].driver,
                  &buses[busCount].totalSeats,
                  &buses[busCount].availableSeats) == 5) {
        busCount++;
    }
    fclose(file);
}

void saveBuses() {
    FILE *file = fopen(BUS_FILE, "w");
    if (!file) return;
    for (int i = 0; i < busCount; i++) {
        fprintf(file, "%d,%s,%s,%d,%d\n",
                buses[i].busId,
                buses[i].route,
                buses[i].driver,
                buses[i].totalSeats,
                buses[i].availableSeats);
    }
    fclose(file);
}

void loadBookings() {
    FILE *file = fopen(BOOKING_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%d,%99[^,],%d\n",
                  &bookings[bookingCount].bookingId,
                  &bookings[bookingCount].busId,
                  bookings[bookingCount].passengerName,
                  &bookings[bookingCount].seatsBooked) == 4) {
        if (bookings[bookingCount].bookingId >= nextBookingId)
            nextBookingId = bookings[bookingCount].bookingId + 1;
        bookingCount++;
    }
    fclose(file);
}

void saveBookings() {
    FILE *file = fopen(BOOKING_FILE, "w");
    if (!file) return;
    for (int i = 0; i < bookingCount; i++) {
        fprintf(file, "%d,%d,%s,%d\n",
                bookings[i].bookingId,
                bookings[i].busId,
                bookings[i].passengerName,
                bookings[i].seatsBooked);
    }
    fclose(file);
}

// ---------- Core Features ----------
void addBus() {
    if (busCount >= MAX_BUSES) {
        printf("Cannot add more buses.\n");
        return;
    }
    printf("Enter Bus ID: ");
    buses[busCount].busId = getIntInput();

    printf("Enter route: ");
    readLine(buses[busCount].route, MAX_LEN);

    printf("Enter driver name: ");
    readLine(buses[busCount].driver, MAX_LEN);

    printf("Enter total seats: ");
    buses[busCount].totalSeats = getIntInput();
    buses[busCount].availableSeats = buses[busCount].totalSeats;

    busCount++;
    printf("Bus added successfully.\n");
}

void viewBuses() {
    if (busCount == 0) {
        printf("No buses available.\n");
        return;
    }
    printf("\nAvailable Buses:\n");
    for (int i = 0; i < busCount; i++) {
        printf("BusID: %d | Route: %s | Driver: %s | Seats: %d/%d\n",
               buses[i].busId,
               buses[i].route,
               buses[i].driver,
               buses[i].availableSeats,
               buses[i].totalSeats);
    }
}

void bookTicket() {
    if (busCount == 0) {
        printf("No buses to book.\n");
        return;
    }
    viewBuses();

    printf("Enter Bus ID to book: ");
    int busId = getIntInput();

    // Find bus by ID
    int busIndex = -1;
    for (int i = 0; i < busCount; i++)
        if (buses[i].busId == busId) { busIndex = i; break; }

    if (busIndex == -1) {
        printf("Bus not found.\n");
        return;
    }

    // Ask number of passengers
    printf("How many passengers in your family/group? ");
    int familyCount = getIntInput();

    if (familyCount > buses[busIndex].availableSeats || familyCount <= 0) {
        printf("Invalid passenger count. Available: %d\n", buses[busIndex].availableSeats);
        return;
    }

    // Ask booking name (head of family)
    printf("Enter booking name (Head of Family): ");
    readLine(bookings[bookingCount].passengerName, MAX_LEN);

    // Collect passenger details (only display, not stored)
    printf("\nEnter details for all %d passengers:\n", familyCount);
    for (int i = 1; i <= familyCount; i++) {
        char tempName[MAX_LEN];
        int seatNo;

        printf("Passenger %d name: ", i);
        readLine(tempName, MAX_LEN);

        printf("Passenger %d seat number: ", i);
        seatNo = getIntInput();

        // Not saved, just shown
        printf("✔ Recorded: %s (Seat %d)\n", tempName, seatNo);
    }

    // Save booking summary
    bookings[bookingCount].bookingId = nextBookingId++;
    bookings[bookingCount].busId = busId;
    bookings[bookingCount].seatsBooked = familyCount;

    // Reduce available seats
    buses[busIndex].availableSeats -= familyCount;
    bookingCount++;

    printf("\nBooking successful for %d passengers. Your Booking ID: %d\n",
           familyCount, bookings[bookingCount - 1].bookingId);
}

void viewBookings() {
    if (bookingCount == 0) {
        printf("No bookings yet.\n");
        return;
    }
    printf("\nBookings List:\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("BookingID: %d | BusID: %d | Name: %s | Seats: %d\n",
               bookings[i].bookingId,
               bookings[i].busId,
               bookings[i].passengerName,
               bookings[i].seatsBooked);
    }
}

void cancelBooking() {
    if (bookingCount == 0) {
        printf("No bookings to cancel.\n");
        return;
    }
    viewBookings();
    printf("Enter Booking ID to cancel: ");
    int id = getIntInput();

    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++)
        if (bookings[i].bookingId == id) { bookingIndex = i; break; }

    if (bookingIndex == -1) {
        printf("Booking not found.\n");
        return;
    }

    // Restore seats to bus
    for (int i = 0; i < busCount; i++)
        if (buses[i].busId == bookings[bookingIndex].busId) {
            buses[i].availableSeats += bookings[bookingIndex].seatsBooked;
            break;
        }

    // Remove booking entry
    for (int i = bookingIndex; i < bookingCount - 1; i++)
        bookings[i] = bookings[i + 1];
    bookingCount--;

    printf("Booking cancelled successfully.\n");
}

// ---------- Utility ----------
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid number. Enter again: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return num;
}

char *readLine(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}
