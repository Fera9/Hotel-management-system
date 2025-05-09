 Hotel-management-system
Console app project for OOP2 course, Hotel Management system

A console-based hotel booking system developed in C++ using core Object-Oriented Programming (OOP) principles and file handling. The system supports two types of users — Customers and Admins — with distinct roles and access levels. Data persistence is implemented through file I/O streams (ifstream, ofstream) without the use of databases or vectors.


---

 OOP Concepts Used

Inheritance: Room types such as OneBedRoom and TwoBedRoom are derived from a base Room class.
Polymorphism: Virtual methods like showInfo() allow dynamic binding for room information display.
Encapsulation: Data members are kept private with public getters and setters for secure data access.
Operator Overloading: Custom operators (==, >, <<, >>) are overloaded for meaningful comparisons and streamlined input/output.
File Handling: All user data, room data, and bookings are saved and loaded via file streams (.txt files).


---

 Roles

 Customer:
- Book a room
- View bookings

 Admin:
- View all bookings
- Book for the customer

---

HotelManagement/
├── main.cpp // Contains login, main menu, program entry point
├── hotel_system.h // Class declarations and method definitions
├── user.txt // Stores customer/admin account data
├── orders.txt // Stores booking records


 💻 How to Compile and Run

1. Compile the project using a C++ compiler that supports C++11 or higher.
2. Run the executable from the terminal/console.
3. Log in/Sign in as Admin or Customer to use respective features.
 

