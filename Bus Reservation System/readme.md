# 🚌 Bus Reservation System in C  
![C Language](https://img.shields.io/badge/Language-C-blue)  
A simple **console-based bus booking application** written in **C**.  
It allows you to **add buses**, **book tickets**, **view buses and bookings**, and **cancel reservations** — all with **persistent storage** in files.

---

## 📂 File Overview  

| File Name                    | Description |
|------------------------------|-------------|
| `Bus-Reservation-system.c`   | 🖥 Main program file with all reservation functionalities. |
| `buses.txt`                  | 🚌 Stores bus details – route, driver, seating info. |
| `bookings.txt`               | 🎟 Stores passenger booking information. |

---

## ✨ Features  

- 🚌 **Add Bus** – Create new bus routes with driver name and seat count.  
- 👀 **View Buses** – Displays available buses, drivers, and seats left.  
- 🎟 **Book Ticket** – Reserve multiple seats for a single booking (supports families/groups).  
- 📋 **View Bookings** – Show all ticket reservations with passenger name and bus details.  
- ❌ **Cancel Booking** – Frees up seats by removing an existing booking.  
- 💾 **Persistent Storage** – Saves data to `buses.txt` and `bookings.txt` automatically.  

---

## ⚙️ How to Compile & Run  

Open terminal and run:  

```

---

## 🖥 Example Usage  

```
===== Bus Reservation System =====
1. Add Bus
2. View Buses
3. Book Ticket
4. View Bookings
5. Cancel Booking
6. Save & Exit
   Enter your choice: 1
   Enter Bus ID: 101
   Enter route: City A to City B
   Enter driver name: John Smith
   Enter total seats: 40
   Bus added successfully.
```

---

## 📌 Notes  

- ⚠️ Maximum **50 buses** and **200 bookings** supported.  
- 📝 Booking IDs are generated automatically.  
- 👨‍👩‍👧‍👦 You can book **multiple seats at once** under a single booking name.  
- 🚫 Program validates inputs to prevent overbooking or invalid entries.  

---

## 📜 License  

🆓 Free to use, modify, and share.
```

***