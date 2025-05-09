#include <iostream>
#include <fstream>

#include "hotel_system.h"

int main() {
    loadData();
    User user = auth();
    if (user.getRole() == "admin") {
        adminSystem(user);
    }
    else if (user.getRole() == "customer") {
        customerSystem(user);
    }
    else {
        cout << "Unknown user type. Exiting." << endl;
     
    }
    return 0;
}

//to load existing users into a global array of User

    const int MAX_USERS = 100;
    User users[MAX_USERS];
    int userCount = 0;

    void loadData() {
        ifstream file("users.txt");
        string name,  password, role;
        int phone_number;

        while (file >> name >> phone_number >> password >> role) {
            users[userCount++] = User(name, phone_number, password, role);
        }
        file.close();
    };


User auth() {
    int choice;
    cout << "1. Login\n2. Register\nChoose option: ";
    cin >> choice;

    if (choice == 1) {
        // Login flow
        int phone_number_input;
        cout << "Phone number: ";
        cin >> phone_number_input;
        string password;
        cout << "Password: ";
        cin >> password;

        // Open users.txt and check credentials
        ifstream file("users.txt");
        string name, filePassword, role;
        int phone_number_file;

        while (file >> name >> phone_number_file >> filePassword >> role) {
            if (phone_number_file == phone_number_input && filePassword == password) {
                file.close();
                return User(name, phone_number_file, password, role);
            }
        }

        file.close();
        cout << "Login failed. Try again.\n";
        return auth(); // restart auth if failed

    }
    else if (choice == 2) {
        // Register flow
        string name, password, role;
        int phone_number;

        cout << "Name: "; cin >> name;
        cout << "Phone number: "; cin >> phone_number;
        cout << "Password: "; cin >> password;
        cout << "Role (admin/customer): "; cin >> role;

        ofstream file("users.txt", ios::app);
        file << name << " " << phone_number << " " << password << " " << role << endl;

        file.close();

        return User(name, phone_number, password, role);
    }

    else {
        cout << "Invalid option. Try again.\n";
        return auth();
    }

};

void adminSystem(const User& user) {
    int choice;
    do {
        cout << "\n===== Admin Menu =====" << endl;
        cout << "1. View all bookings" << endl;
        cout << "2. Book a room for customer" << endl;
        cout << "3. Leave a receipt" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewAllBookings();
            break;
        case 2:
            bookRoomForCustomer();
            break;
        case 3:
            leaveReceipt();
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

void customerSystem(const User& user) {
    int choice;
    do {
        cout << "\n===== Customer Menu =====" << endl;
        cout << "1. Book a room" << endl;
        cout << "2. View my bookings" << endl;
        cout << "3. Make a payment" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bookRoom(user);
            break;
        case 2:
            viewMyBookings(user);
            break;
        case 3:
            makePayment(user);
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
};


void bookRoom(const User& user) {
    int choice;
    cout << "Select room type:\n";
    cout << "1. One-Bedroom ($100)\n";
    cout << "2. Two-Bedroom ($200)\n";
    cout << "Enter choice: ";
    cin >> choice;

    Room* selectedRoom;
    if (choice == 1) {
        selectedRoom = new OneBedRoom();
    }
    else if (choice == 2) {
        selectedRoom = new TwoBedRoom();
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    string date;
    cout << "Enter booking date (e.g. 2025-05-10): ";
    cin >> date;

    // Create order
    Order order(user.getPhone_number(), selectedRoom->getRoom_type(), selectedRoom->getPrice(), date);

    // Save to file
    ofstream outFile("orders.txt", ios::app);
    if (outFile.is_open()) {
        outFile << order.getcustomerPhone_number() << " "
            << order.getRoom_type() << " "
            << order.getPrice() << " "
            << order.getDate() << "\n";
        outFile.close();
        cout << "Room booked successfully!\n";
    }
    else {
        cout << "Error opening orders file.\n";
    }

    delete selectedRoom;
}

void viewMyBookings(const User& user) {
    ifstream inFile("orders.txt");
    if (!inFile) {
        cout << "Error opening orders file.\n";
        return;
    }

    int phone;
    string room;
    int price;
    string date;
    bool found = false;

    while (inFile >> phone >> room >> price >> date) {
        if (phone == user.getPhone_number()) {
            cout << "Room: " << room << ", Price: $" << price << ", Date: " << date << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No bookings found.\n";
    }

    inFile.close();
}



    void makePayment(const User & user) {
        ifstream inFile("orders.txt");
        if (!inFile) {
            cout << "Error opening orders file.\n";
            return;
        }

        int phone;
        string room;
        int price;
        string date;
        bool found = false;
        Order lastOrder;

        // read the file and search for the price
        while (inFile >> phone >> room >> price >> date) {
            if (phone == user.getPhone_number()) {
                lastOrder = Order(phone, room, price, date);
                found = true;
            }
        }

        inFile.close();

        if (!found) {
            cout << "No bookings found. Please book a room first.\n";
            return;
        }

        cout << "You have a pending booking:\n";
        lastOrder.showOrder();

        double amount;
        while (true) {
            cout << "Enter payment amount: $";
            cin >> amount;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
                continue;
            }

            if (amount == lastOrder.getPrice()) {
                cout << "Payment successful! Thank you.\n";
                break;
            }
            else {
                cout << "Incorrect amount. Please enter exactly $" << lastOrder.getPrice() << ".\n";
            }
        }
    }


void viewAllBookings() {
    ifstream inFile("orders.txt");
    if (!inFile) {
        cout << "Error opening orders file.\n";
        return;
    }

    int phone;
    string room;
    int price;
    string date;
    bool found = false;

    cout << "\nAll Bookings:\n";
    while (inFile >> phone >> room >> price >> date) {
        cout << "Customer Phone: " << phone << ", Room: " << room
            << ", Price: $" << price << ", Date: " << date << endl;
        found = true;
    }

    if (!found) {
        cout << "No bookings found.\n";
    }

    inFile.close();
}

void bookRoomForCustomer() {
    int phone;
    cout << "Enter customer's phone number: ";
    cin >> phone;
    bool valid = false;
    do {
        cout << "Enter customer's phone number: ";
        cin >> phone;

        for (int i = 0; i < userCount; ++i) {
            if (users[i].getPhone_number() == phone && users[i].getRole() == "customer") {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "No customer found with this phone number. Try again.\n";
        }

    } while (!valid);

    int choice;
    cout << "Select room type:\n";
    cout << "1. One-Bedroom ($100)\n";
    cout << "2. Two-Bedroom ($200)\n";
    cout << "Enter choice: ";
    cin >> choice;

    Room* selectedRoom;
    if (choice == 1) {
        selectedRoom = new OneBedRoom();
    }
    else if (choice == 2) {
        selectedRoom = new TwoBedRoom();
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    string date;
    cout << "Enter booking date (e.g. 2025-05-10): ";
    cin >> date;

    Order order(phone, selectedRoom->getRoom_type(), selectedRoom->getPrice(), date);

    ofstream outFile("orders.txt", ios::app);
    if (outFile.is_open()) {
        outFile << order.getcustomerPhone_number() << " "
            << order.getRoom_type() << " "
            << order.getPrice() << " "
            << order.getDate() << "\n";
        outFile.close();
        cout << "Room booked successfully for customer!\n";
    }
    else {
        cout << "Error opening orders file.\n";
    }

    delete selectedRoom;
}

void leaveReceipt() {
    cout << "Receipt left successfully! (simulated)\n";
}
