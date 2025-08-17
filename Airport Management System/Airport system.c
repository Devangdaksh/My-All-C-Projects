//
// Simple Airport Management System in C
// Features: add flights, book seats, cancel bookings, view flights/bookings
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 200
#define MAX_LEN 100

#define FLIGHT_FILE "flights.txt"
#define BOOKING_FILE "flight_bookings.txt"

// ---------- Structures ----------

typedef struct {
    int flightId;
    char flightNum[MAX_LEN];
    char origin[MAX_LEN];
    char destination[MAX_LEN];
    char departTime[MAX_LEN];
    int totalSeats;
    int availableSeats;
} Flight;

typedef struct {
    int bookingId;
    int flightId;
    char passengerName[MAX_LEN];
    int seatsBooked;
} Booking;

// ---------- Global Variables ----------
Flight flights[MAX_FLIGHTS];
int flightCount = 0;

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

int nextBookingId = 1;

// ---------- Function Prototypes ----------
void loadFlights();
void saveFlights();
void loadBookings();
void saveBookings();

void addFlight();
void viewFlights();
void bookSeats();
void viewBookings();
void cancelBooking();

int getIntInput();
char *readLine(char *buffer, int size);

// ---------- Main ----------
int main() {
    loadFlights();
    loadBookings();

    int choice;
    while (1) {
        printf("\n=== Airport Management System ===\n");
        printf("1. Add Flight\n");
        printf("2. View Flights\n");
        printf("3. Book Seats\n");
        printf("4. View Bookings\n");
        printf("5. Cancel Booking\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: addFlight(); break;
            case 2: viewFlights(); break;
            case 3: bookSeats(); break;
            case 4: viewBookings(); break;
            case 5: cancelBooking(); break;
            case 6:
                saveFlights();
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
void loadFlights() {
    FILE *file = fopen(FLIGHT_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%d\n",
                  &flights[flightCount].flightId,
                  flights[flightCount].flightNum,
                  flights[flightCount].origin,
                  flights[flightCount].destination,
                  flights[flightCount].departTime,
                  &flights[flightCount].totalSeats,
                  &flights[flightCount].availableSeats) == 7) {
        flightCount++;
    }
    fclose(file);
}

void saveFlights() {
    FILE *file = fopen(FLIGHT_FILE, "w");
    if (!file) return;
    for (int i = 0; i < flightCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%d\n",
                flights[i].flightId,
                flights[i].flightNum,
                flights[i].origin,
                flights[i].destination,
                flights[i].departTime,
                flights[i].totalSeats,
                flights[i].availableSeats);
    }
    fclose(file);
}

void loadBookings() {
    FILE *file = fopen(BOOKING_FILE, "r");
    if (!file) return;
    while (fscanf(file, "%d,%d,%99[^,],%d\n",
                  &bookings[bookingCount].bookingId,
                  &bookings[bookingCount].flightId,
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
                bookings[i].flightId,
                bookings[i].passengerName,
                bookings[i].seatsBooked);
    }
    fclose(file);
}

// ---------- Core Functions ----------
void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Cannot add more flights.\n");
        return;
    }
    Flight newFlight;
    newFlight.flightId = flightCount + 1;

    printf("Flight Number: ");
    readLine(newFlight.flightNum, MAX_LEN);

    printf("Origin City: ");
    readLine(newFlight.origin, MAX_LEN);

    printf("Destination City: ");
    readLine(newFlight.destination, MAX_LEN);

    printf("Departure Time (e.g. 14:00): ");
    readLine(newFlight.departTime, MAX_LEN);

    printf("Total Seats: ");
    newFlight.totalSeats = getIntInput();
    newFlight.availableSeats = newFlight.totalSeats;

    flights[flightCount++] = newFlight;
    printf("Flight added!\n");
}

void viewFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }
    printf("\nList of Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("ID:%d | Flight:%s | From:%s | To:%s | Time:%s | Seats:%d/%d\n",
               flights[i].flightId, flights[i].flightNum, flights[i].origin,
               flights[i].destination, flights[i].departTime,
               flights[i].availableSeats, flights[i].totalSeats);
    }
}

void bookSeats() {
    if (flightCount == 0) {
        printf("No flights to book.\n");
        return;
    }
    viewFlights();

    printf("Enter Flight ID to book: ");
    int id = getIntInput();

    int idx = -1;
    for (int i = 0; i < flightCount; i++)
        if (flights[i].flightId == id) { idx = i; break; }

    if (idx == -1) {
        printf("Flight not found.\n");
        return;
    }

    printf("Passenger Name: ");
    readLine(bookings[bookingCount].passengerName, MAX_LEN);

    printf("Number of seats to book: ");
    int seats = getIntInput();

    if (seats > flights[idx].availableSeats || seats <= 0) {
        printf("Invalid seats. Available: %d\n", flights[idx].availableSeats);
        return;
    }

    bookings[bookingCount].bookingId = nextBookingId++;
    bookings[bookingCount].flightId = id;
    bookings[bookingCount].seatsBooked = seats;

    flights[idx].availableSeats -= seats;
    bookingCount++;

    printf("Booked! Booking ID: %d\n", bookings[bookingCount - 1].bookingId);
}

void viewBookings() {
    if (bookingCount == 0) {
        printf("No bookings yet.\n");
        return;
    }
    printf("\nBookings:\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("BookingID:%d | FlightID:%d | Name:%s | Seats:%d\n",
               bookings[i].bookingId, bookings[i].flightId,
               bookings[i].passengerName, bookings[i].seatsBooked);
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

    int idx = -1;
    for (int i = 0; i < bookingCount; i++)
        if (bookings[i].bookingId == id) { idx = i; break; }

    if (idx == -1) {
        printf("Booking not found.\n");
        return;
    }
    // Free seats in flight
    for (int i = 0; i < flightCount; i++)
        if (flights[i].flightId == bookings[idx].flightId)
            flights[i].availableSeats += bookings[idx].seatsBooked;

    // Remove booking from list
    for (int i = idx; i < bookingCount - 1; i++)
        bookings[i] = bookings[i + 1];
    bookingCount--;

    printf("Booking cancelled!\n");
}

// ---------- Utility ----------
int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Enter a number: ");
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
