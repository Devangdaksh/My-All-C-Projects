# 🏦 Bank Management System in C

![C Language](https://img.shields.io/badge/Language-C-blue)

A simple **console-based bank management application** written in **C**.  
Allows users to **add, view, and delete accounts**, **deposit/withdraw money**, and **check balance**—with persistent file storage.

---

## 📂 File Overview

| File Name           | Description |
|---------------------|-------------|
| `bank-system.c`     | 🖥 Main program with all account and banking operations |
| `accounts.txt`      | 🗃 Stores all account information (number, holder, balance) |

---

## ✨ Features

- ➕ **Add Account** – Create new accounts with account number, holder name, and opening deposit
- 👀 **View Accounts** – List all accounts with balance information
- 💰 **Deposit Money** – Add funds to any account
- 🏧 **Withdraw Money** – Remove funds (preventing overdrafts)
- 🧾 **Check Balance** – See current balance for a specific account number
- ❌ **Delete Account** – Remove closed accounts
- 💾 **Persistent Storage** – All changes are saved automatically to `accounts.txt`
- 🚦 **Input Safety** – Validates numeric input for amounts and account existence

## 🖥 Example Usage

```
=== Bank Management System ===
1. Add Account
2. View Accounts
3. Deposit Money
4. Withdraw Money
5. Check Balance
6. Delete Account
7. Save and Exit
Enter your choice: 1
Enter Account Number: 101
Enter Account Holder Name: Alice Smith
Enter Initial Deposit Amount: 2500
Account created successfully!
```

---

## 📌 Notes

- ⚠️ Maximum **100 accounts** supported
- 🔢 Each account must have a unique account number
- 🛡 Withdrawals not allowed if insufficient funds (no negative balances)
- 📝 All changes are saved immediately to disk—no risk of losing progress

---

## 📜 License

🆓 Free to use, modify, and share.