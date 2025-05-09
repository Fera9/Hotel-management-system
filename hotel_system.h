#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
    string name;
    int phone_number;
    string password;
    string role;
public:
    User() {
        name = "";
        phone_number = 0;
        password = "";
        role = "";
    }

    User(string name, int phone_number, string password, string role) {
        this->name = name;
        this->phone_number = phone_number;
        this->password = password;
        this->role = role;
    }

    // Getters
    string getName() { return name; }
    int getPhone_number() const { return phone_number; }
    string getPassword() { return password; }
    string getRole() { return role; }
};

class Room {
private:
    string room_type;
    int price;
public:
    Room() {
        room_type = "";
        price = 0;
    }

    Room(string room_type, int price) {
        this->room_type = room_type;
        this->price = price;
    }

    string getRoom_type() { return room_type; }
    int getPrice() { return price; }

    virtual void showInfo() {
        cout << "Room type: " << room_type << ", Price: $" << price << endl;
    }
};

class OneBedRoom : public Room {
public:
    OneBedRoom() : Room("One-Bedroom", 100) {}
};

class TwoBedRoom : public Room {
public:
    TwoBedRoom() : Room("Two-Bedroom", 200) {}
};

class Order {
private:
    int customerPhone_number;
    string room_type;
    int price;
    string date;
public:
    Order() {
        customerPhone_number = 0;
        room_type = "";
        price = 0;
        date = "";
    }

    Order(int customerPhone_number, string room_type, int price, string date) {
        this->customerPhone_number = customerPhone_number;
        this->room_type = room_type;
        this->price = price;
        this->date = date;
    }

    int getcustomerPhone_number() const { return customerPhone_number; }
    string getRoom_type() const { return room_type; }
    int getPrice() const { return price; }
    string getDate() const { return date; }

    void showOrder() const {
        cout << "Customer: " << customerPhone_number << ", Room: " << room_type
            << ", Price: $" << price << ", Date: " << date << endl;
    }
};


// function declarations????

void loadData();
User auth();
void adminSystem(const User& user);
void customerSystem(const User& user);
void bookRoom(const User& user);

void viewMyBookings(const User& user);
void makePayment(const User& user);
void viewAllBookings();
void bookRoomForCustomer();
void leaveReceipt();
