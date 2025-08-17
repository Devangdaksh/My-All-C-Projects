# ✈️ Airport Management System in C
![C Language](https://img.shields.io/badge/Language-C-blue)

A simple **console-based airport management application** written in **C**.  
It allows you to **add flights**, **book seats**, **view flights and bookings**, and **cancel reservations**—all with persistent file storage.

---

## 📂 File Overview

| File Name                | Description |
|--------------------------|-------------|
| `Airport-system.c`       | 🖥 Main program file, contains all features and logic |
| `flights.txt`            | ✈️ Stores flight details—flight numbers, routes, departure times, seating info |
| `flight_bookings.txt`    | 🎫 Stores passenger booking information and seat reservations |

---

## ✨ Features

- ✈️ **Add Flight** – Create new flights with origin, destination, departure time, and seat capacity
- 👀 **View Flights** – Displays all available flights with seat information
- 🎫 **Book Seats** – Reserve multiple seats for passengers on specific flights
- 📋 **View Bookings** – Show all flight reservations with passenger and seat details
- ❌ **Cancel Booking** – Remove existing bookings and free up seats
- 💾 **Persistent Storage** – Automatically saves all data to `flights.txt` and `flight_bookings.txt`


## 🖥 Example Usage

```
=== Airport Management System ===
1. Add Flight
2. View Flights
3. Book Seats
4. View Bookings
5. Cancel Booking
6. Save & Exit
Enter your choice: 1
Flight Number: AI101
Origin City: Delhi
Destination City: Mumbai
Departure Time (e.g. 14:00): 15:30
Total Seats: 180
Flight added!
```

---

## 📌 Notes

- ⚠️ Maximum **100 flights** and **200 bookings** supported
- 🎫 Booking IDs are generated automatically
- 🛂 Multiple seats can be booked under a single passenger name
- 🚫 Overbooking and invalid entries are prevented
- 🌍 Supports any origin/destination city names and flexible departure times

---

## 📜 License

🆓 Free to use, modify, and share.