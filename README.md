# UniStay-Rental-System
A console-based Rental Management System in C++ implementing DSA concepts including Linked Lists, Stacks, Queues, Trees, Graphs, Sorting and Searching Algorithms.

---

## Overview 
UniStay is a rental property management system that allows administrators and tenants to manage their rental units, tenant accounts, reservations, billing, and maintenance requests using a console application. The project serves as a practical application of fundamental Data Structures and Algorithms (DSA) concepts learned throughout the course while following modular software design practices.

---

# Technologies Used:
- C++ 
- Object-Oriented Programming (OOP) 
- Standard Template Library (STL) 
- File Handling 
- Git & GitHub

---

# Project Structure

UniStay-Rental-System/
|
|-- src/
|   |
|   |-- authentication/
|   |   |-- Login.cpp
|   |   `-- Login.h
|   |
|   |-- billing/
|   |   |-- Billing.cpp
|   |   |-- Billing.h
|   |   |-- Payment.cpp
|   |   `-- Payment.h
|   |
|   |-- booking/
|   |   |-- Reservation.cpp
|   |   `-- Reservation.h
|   |
|   |-- dsa/
|   |   |-- BinaryTree.cpp
|   |   |-- Graph.cpp
|   |   |-- LinkedList.cpp
|   |   |-- Queue.cpp
|   |   |-- Searching.cpp
|   |   |-- Sorting.cpp
|   |   |-- Sorting.h
|   |   `-- Stack.cpp
|   |
|   |-- maintenance/
|   |   |-- Complaint.cpp
|   |   |-- Complaint.h
|   |   |-- Maintenance.cpp
|   |   `-- Maintenance.h
|   |
|   |-- property/
|   |   |-- Unit.cpp
|   |   `-- Unit.h
|   |
|   |-- reports/
|   |   |-- Reports.cpp
|   |   `-- Reports.h
|   |
|   |-- users/
|   |   |-- Admin.cpp
|   |   |-- Admin.h
|   |   |-- Guardian.cpp
|   |   |-- Guardian.h
|   |   |-- Tenant.cpp
|   |   `-- Tenant.h
|   |
|   `-- main.cpp
|
|-- data/
|   |-- bookings.csv
|   |-- complaints.csv
|   |-- guardians.csv
|   |-- payments.csv
|   |-- tenants.csv
|   `-- units.csv
|
|-- docs/
|   `-- Pseudocode and Flowchart.pdf
|
|-- .vscode/
|-- build.bat
|-- README.md
`-- .gitignore

## Folder Description

| Folder | Description |
|---------|-------------|
| `src/` | Contains all source code for the system. |
| `authentication/` | Login and authentication functions. |
| `billing/` | Billing and payment management. |
| `booking/` | Reservation-related functionality. |
| `dsa/` | Implementations of required Data Structures and Algorithms. |
| `maintenance/` | Complaint and maintenance management. |
| `property/` | Rental unit management. |
| `reports/` | Report generation module. |
| `users/` | Administrator, tenant, and guardian management. |
| `data/` | Stores CSV files used for persistent data. |
| `docs/` | Project documentation, pseudocode, and flowcharts. |

## Current Features

The following features are currently implemented in the UniStay Rental System.

### Authentication

* Administrator login
* Tenant login
* Tenant registration
* Authentication validation

### Property Management

* View all rental units
* Add new rental units
* Remove existing rental units

### Tenant Management

* View tenant information
* Remove tenant records

### Billing and Payment

* Process tenant payments
* Undo the latest payment transaction

### Maintenance Management

* Submit maintenance complaints
* View submitted complaints
* Process maintenance complaints

### Data Persistence

The system automatically loads and saves data using CSV files.

Current data files include:

* `units.csv`
* `tenants.csv`
* `complaints.csv`
* `payments.csv`
* `bookings.csv`
* `guardians.csv`

---

# Programming Concepts Demonstrated

This project is made to demonstrate the application of the Data Structures and Algorithms (CCS0015) topics discussed throughout the course.

| Topic                | Purpose in UniStay                         | Status  |
| -------------------- | ------------------------------------------ | ------- |
| Pointers             | Dynamic object management                  | Planned |
| Linked List          | Dynamic storage of tenant and unit records | Planned |
| Stack                | Undo payment transactions                  | Planned |
| Queue                | Reservation processing                     | Planned |
| Recursion            | Recursive algorithm demonstrations         | Planned |
| Binary Search Tree   | Fast searching of tenants and units        | Planned |
| Graph                | Property and maintenance relationships     | Planned |
| Sorting Algorithms   | Sort tenant and property records           | Planned |
| Searching Algorithms | Locate records efficiently                 | Planned |

---

# Development Progress

| Module                 | Status               |
| ---------------------- | -------------------- |
| Authentication         | Completed            |
| Property Management    | Completed            |
| Tenant Management      | Completed            |
| Billing                | Basic Implementation |
| Complaint Management   | Basic Implementation |
| Reservation System     | In Development       |
| Data Structure Modules | In Development       |
| Reports                | Planned              |
| Guardian Module        | Planned              |
| Console Interface      | Improving            |

---

# How to Build and Run

## Requirements

Before compiling make sure the following are installed:

* MinGW g++
* Windows Command Prompt or PowerShell

Verify your compiler by running:

```bash
g++ --version
```

---

## Build

The recommended way to build the project is by using the provided build script.

```bash
build.bat
```

Alternatively, compile manually:

```bash
g++ src/main.cpp src/authentication/Login.cpp src/property/Unit.cpp src/maintenance/Complaint.cpp src/users/Admin.cpp src/users/Tenant.cpp src/dsa/Sorting.cpp -o unistay.exe
```

---

## Run

After compiling successfully:

```bash
unistay.exe
```

Or just run **build.bat** to auto compile and launch the prorgam.

---

# Changelog

This section records significant updates made throughout the project's development.

## Version 1.0

* Initial project structure
* Administrator and tenant authentication
* Property management
* Tenant management

## Version 1.1 (6/26/26)

* Created overall prototype including admin login
* Tenant login
* Register tenant
* Units and tenants (hash table)
* Unit functions (view, add, and remove)
* Tenant functions (removal and view)
* Payment process with undo feature (undostack)
* Complaint management for admin and tenant (queue).

## Version 2.0 (6/28/26)

* Added build.bat for auto compile and launch
* Improved console interface
* Code documentation
* Project documentation
* Prepared DSA implementation modules
* Improved README section

---

# Developer Notes

### 6/28/26
**Developer:** AJ
**Module(s):**
* Main Menu
* Admin Portal
* Project Documentation

**Summary:**
Improved the console interface and standardized project documentation.

**Changes Made**

* Added:
  * `build.bat`
  * Documentation templates for blank source files
* Modified:
  * Redesigned the Main Menu interface
  * Improved the Admin Dashboard layout
  * Updated the README
* Removed:
  * put csv files here.txt
* Fixed:
  * Improved menu readability

**Files Affected**
* `src/main.cpp`
* `README.md`
* `build.bat`

**Notes**
* Console utility functions could be moved into a dedicated `Console` module in a future update.

---
# Known Issues

* Reservation system is still under development.
* DSA modules are prepared but not yet integrated into the system.
* Reporting module has not yet been implemented.
* Console interface is still being refined.

---

# Contributors

| Role             | Member |
| ---------------- | ------ |
| Leader | Angelika Abendanio |
| Assistant Leader | Cyrus Elecanal |
| Main Programmer | Kyle Mendoza |
| Research/Documentation | Gene Hilario |
| Research/Documentation | Jaiceryn Dela Cruz |
| Research/Documentation | Alaina Rocreo |

---

FEU Institute of Technology
Bachelor of Science in Computer Science with Specialization in AI