# 🏥 Hospital Management System in C  
![C Language](https://img.shields.io/badge/Language-C-blue)  

A simple **console-based hospital management program** written in **C** that allows you to manage patient records — including **adding**, **viewing**, **deleting**, and **saving/loading** data from a file.  

---

## 📂 File Overview  

| File Name                | Description |
|--------------------------|-------------|
| `Hospital-management.c`  | 💉 Main C program that manages hospital patient records using file handling. |
| `patients.txt`           | 📑 Data file storing patient records (auto-created if not found). |

---

## ✨ Features  

- ➕ **Add Patient** – Enter name, age, gender, and diagnosis.  
- 👀 **View Patient List** – Displays all stored patient records.  
- ❌ **Delete Patient Record** – Remove a patient by their record number.  
- 💾 **Persistent Storage** – Saves all patient records to `patients.txt` so data is kept after restart.  
- ⚠️ **Input Validation** – Prevents invalid numeric inputs.  


## 🖥 Example Usage  

```
===== Hospital Management System =====
1. Add Patient Record
2. View Patient Records
3. Delete Patient Record
4. Save and Exit
Enter your choice: 1
Enter patient name: John Doe
Enter age: 30
Enter gender (Male/Female/Other): Male
Enter diagnosis: Fever
Patient record added successfully!
```

---

## 📌 Notes  

- 📝 Maximum **100 patients** supported.  
- 📄 Data file is stored as a simple CSV format in `patients.txt`.  
- 🚫 Deleting a record shifts remaining entries so numbering stays correct.  
- 💻 Works on Linux, Mac, and Windows (with GCC).  

---

## 📜 License  

🆓 Free to use, modify, and share.
```

***