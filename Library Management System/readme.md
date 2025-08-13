# 📚 Library Management Systems in C  
![C Language](https://img.shields.io/badge/Language-C-blue)

This repository contains **two versions** of a Library Management System written in **C**:  
1. **📝 Basic Version (`Library-Management.c`)** – Manage books with simple add, view, and delete operations.  
2. **🚀 Advanced Version (`Library-Management-advance.c`)** – Full-featured system with members, borrowing, and returning books.

---

## 📂 Files Overview  

| File Name | Description |
|-----------|-------------|
| `Library-Management.c` | 📖 Simple library system – add, view, and delete books with file storage. |
| `Library-Management-advance.c` | 🏛 Advanced library system – adds member management, borrow/return tracking, and persistent storage. |

---

## ✨ Features  

### 📝 Basic Version
- 📚 **Add Book** – Store title, author, ISBN, and quantity.
- 👀 **View Books** – List all books in the library.
- ❌ **Delete Book** – Remove a book by its record number.
- 💾 **File Storage** – Saves and loads data from `library_books.txt`.

### 🚀 Advanced Version
- ➕ **Add Books**
- 🧑‍🤝‍🧑 **Add Members**
- 👀 **View Members & Books**
- 📥 **Borrow Book** (with quantity updates)
- 📤 **Return Book**
- 🚫 **Validation** for invalid inputs or unavailable books
- 💾 Persistent storage across:
  - `library_books.txt`
  - `library_members.txt`
  - `library_borrows.txt`

---

## 🖥 Example (Advanced Version)

```
===== Library Management System =====
1. Add Book
2. View Books
3. Delete Book
4. Add Member
5. View Members
6. Borrow Book
7. Return Book
8. Save & Exit
   Enter your choice: 1
   Enter title: C Programming
   Enter author: Dennis Ritchie
   Enter ISBN: 12345
   Enter quantity: 3
   Book added.
```

---

## 📌 Notes  
- ⚠️ Avoid editing data files manually unless you know the format.  
- The **basic version** works well for quick demos and small datasets.  
- The **advanced version** is ideal for multi-user scenarios with borrowing/returning features.  

---

## 📜 License   
🆓 Free to use, modify, and share.

## 🙋‍♂️ Credits

Created by **Devang**  
📧 [Email](mailto:devangkumarprajapati1908@gmail.com)  
📸 [Instagram](https://www.instagram.com/dev_daksh__/)  
💼 [LinkedIn](https://www.linkedin.com/in/devang-kumar-prajapati-1908/)  
🐙 [GitHub](https://github.com/Devangdaksh)