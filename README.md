# 📚 C++ Library Management System

A simple **console-based Library Management System** developed in **C++** for the university unit **Programming and Problem Solving(CSC 121)**. The system demonstrates fundamental programming and **Object-Oriented Programming (OOP)** concepts by simulating a basic library environment where books and students can be managed and borrowing transactions recorded.

The program allows users to add books, register students, search records, and borrow books through a menu-driven interface. Basic data persistence is implemented using file handling to store records.

This project was developed as a **group project** to practice programming, problem-solving, and system design using C++.

---

# 🎯 Project Purpose

The main goal of this project is to demonstrate how programming can be used to solve real-world problems such as **library record management**.

The system was designed to help students understand:

* Object-Oriented Programming in C++
* Data organization using classes
* File handling for data storage
* Menu-driven program design
* Logical problem solving

---

# ✨ Features

## 📖 Book Management

* Add new books to the library
* Prevent duplicate book IDs
* Store book details:

  * Book ID
  * Title
  * Author
  * Year of publication
* Track book availability

## 👨‍🎓 Student Management

* Register students in the system
* Store student information including:

  * Student number
  * Name
  * Programme
  * Year of study

## 🔎 Search Functionality

The system allows searching records easily.

### Book Search

Users can search books by:

* Book ID
* Book Title

### Student Search

Users can search students by:

* Student ID
* Student last name

## 📚 Borrowing System

* Students can borrow books
* Each student can borrow **up to 3 books**
* A student cannot borrow the **same title twice**
* Book availability is automatically updated

## 💾 Data Persistence

The system stores records using text files.

* `books.txt` → stores book records
* `students.txt` → stores student records

---

# 🧠 Concepts Demonstrated

This project demonstrates several **core C++ programming concepts**.

## Object-Oriented Programming

* Classes and Objects
* Encapsulation
* Inheritance
* Nested Classes

## Class Relationships

```
Person
   │
   └── Student
```

### Classes Implemented

**Book Class**

* Stores book information
* Tracks borrowing status

**Person Class**

* Stores personal details
* Contains a nested `Address` class

**Student Class**

* Inherits from `Person`
* Manages borrowing records
* Enforces borrowing limits

## Data Structures

The program uses:

* `vector<Book>` to store books
* `vector<Student>` to store students

## File Handling

The system uses:

* `ofstream`
* Text files for data storage

## Program Flow Control

* Menu-driven interface
* Conditional logic
* Input validation

---

# 🏗️ Project Structure

```
Library-Management-System/
│
├── library.cpp
├── books.txt
├── students.txt
└── README.md
```

### File Descriptions

**library.cpp**
Main program file containing:

* Class definitions
* System logic
* Menu interface

**books.txt**
Stores book records.

**students.txt**
Stores student records.

**README.md**
Project documentation.

---

# ▶️ How to Compile and Run

## 1️⃣ Requirements

You need a **C++ compiler**, such as:

* `g++`
* MinGW (Windows)
* GCC (Linux/macOS)

---

## 2️⃣ Compile the Program

Open a terminal inside the project folder and run:

```bash
g++ library.cpp -o library
```

---

## 3️⃣ Run the Program

### Linux / macOS

```bash
./library
```

### Windows

```bash
library.exe
```

---

## 4️⃣ Program Menu

When the program starts, the following menu appears:

```
===== LIBRARY MENU =====
1 Add Book
2 Add Student
3 Search Book
4 Search Student
5 Borrow Book
6 Exit
```

Enter the number corresponding to the operation you want to perform.

---

# 🔮 Future Improvements

This project can be expanded with additional features such as:

* Return book functionality
* Borrowing history tracking
* Advanced search options (author, year, etc.)
* Database integration (MySQL or SQLite)
* Graphical User Interface (GUI)
* Web-based library system
* Modular architecture using header and source files
* User authentication for librarians and students

These improvements would make the system closer to a **real-world library management system**.

---

# 👥 Group Members

* Itumo Cliff
* Joseph Mwoni
* Ali Gift
* Shervin Abbey
* Gloria Kimanzi
* Benard Wachira
* Roy Mwendwa
* Ian Mwangi
* Brian Kimani
* Dorian Kimani
* John Mboya
