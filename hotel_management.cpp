#include <iostream>
#include <string>

using namespace std;

// Class to represent a Room in the hotel
class Room {
private:
    int roomNumber;
    string roomType;
    double roomPrice;
    bool isBooked;

public:
    Room() : roomNumber(0), roomType(""), roomPrice(0.0), isBooked(false) {}

    void setRoomDetails(int number, string type, double price) {
        roomNumber = number;
        roomType = type;
        roomPrice = price;
        isBooked = false; // Room initially available
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    string getRoomType() const {
        return roomType;
    }

    double getRoomPrice() const {
        return roomPrice;
    }

    bool getBookingStatus() const {
        return isBooked;
    }

    void bookRoom() {
        isBooked = true;
    }

    void releaseRoom() {
        isBooked = false;
    }

    void displayRoomDetails() const {
        cout << "Room Number: " << roomNumber
             << ", Type: " << roomType
             << ", Price: $" << roomPrice
             << ", Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
};

// Class to represent a Guest staying at the hotel
class Guest {
private:
    string name;
    string phoneNumber;
    string address;
    string checkInDate;
    string checkOutDate;

public:
    Guest() : name(""), phoneNumber(""), address(""), checkInDate(""), checkOutDate("") {}

    void setGuestDetails(string guestName, string phone, string addr, string checkIn, string checkOut) {
        name = guestName;
        phoneNumber = phone;
        address = addr;
        checkInDate = checkIn;
        checkOutDate = checkOut;
    }

    string getName() const {
        return name;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getAddress() const {
        return address;
    }

    string getCheckInDate() const {
        return checkInDate;
    }

    string getCheckOutDate() const {
        return checkOutDate;
    }

    void displayGuestDetails() const {
        cout << "Name: " << name << ", Phone: " << phoneNumber
             << ", Address: " << address
             << ", Check-In Date: " << checkInDate
             << ", Check-Out Date: " << checkOutDate << endl;
    }
};

// Class to manage the entire hotel, including rooms and guests
class Hotel {
private:
    Room rooms[100]; // Array to hold up to 100 rooms
    Guest guests[100]; // Array to hold up to 100 guests
    int roomCount;
    int guestCount;

public:
    Hotel() : roomCount(0), guestCount(0) {}

    // Add a new room to the hotel
    void addRoom() {
        int number;
        string type;
        double price;

        cout << "Enter room number: ";
        cin >> number;
        cout << "Enter room type (Single/Double/Suite): ";
        cin >> type;
        cout << "Enter room price: ";
        cin >> price;

        rooms[roomCount].setRoomDetails(number, type, price);
        roomCount++;

        cout << "Room " << number << " added successfully.\n";
    }

    // Display all rooms in the hotel
    void displayRooms() {
        if (roomCount == 0) {
            cout << "No rooms available.\n";
            return;
        }

        cout << "\nRoom List:\n";
        for (int i = 0; i < roomCount; i++) {
            rooms[i].displayRoomDetails();
        }
    }

    // Search for a room by type
    void searchRoomByType() {
        string type;
        bool found = false;

        cout << "Enter room type to search (Single/Double/Suite): ";
        cin >> type;

        cout << "\nSearch Results for Room Type \"" << type << "\":\n";
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].getRoomType() == type) {
                rooms[i].displayRoomDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No rooms of type " << type << " found.\n";
        }
    }

    // Search for a room by price range
    void searchRoomByPrice() {
        double minPrice, maxPrice;
        bool found = false;

        cout << "Enter minimum price: ";
        cin >> minPrice;
        cout << "Enter maximum price: ";
        cin >> maxPrice;

        cout << "\nSearch Results for Rooms priced between $" << minPrice << " and $" << maxPrice << ":\n";
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].getRoomPrice() >= minPrice && rooms[i].getRoomPrice() <= maxPrice) {
                rooms[i].displayRoomDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No rooms found in the specified price range.\n";
        }
    }

    // Add a new guest to the hotel
    void addGuest() {
        string name, phone, address, checkIn, checkOut;

        cout << "Enter guest name: ";
        cin.ignore(); // To clear newline character from previous input
        getline(cin, name);
        cout << "Enter guest phone number: ";
        getline(cin, phone);
        cout << "Enter guest address: ";
        getline(cin, address);
        cout << "Enter check-in date (DD/MM/YYYY): ";
        getline(cin, checkIn);
        cout << "Enter check-out date (DD/MM/YYYY): ";
        getline(cin, checkOut);

        guests[guestCount].setGuestDetails(name, phone, address, checkIn, checkOut);
        guestCount++;

        cout << "Guest " << name << " added successfully.\n";
    }

    // Display all guests in the hotel
    void displayGuests() {
        if (guestCount == 0) {
            cout << "No guests found.\n";
            return;
        }

        cout << "\nGuest List:\n";
        for (int i = 0; i < guestCount; i++) {
            guests[i].displayGuestDetails();
        }
    }

    // Book a room for a guest
    void bookRoom() {
        int roomNumber;
        string guestName;

        cout << "Enter room number to book: ";
        cin >> roomNumber;
        cin.ignore(); // To handle newline character after entering room number
        cout << "Enter guest name for booking: ";
        getline(cin, guestName);

        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].getRoomNumber() == roomNumber) {
                if (!rooms[i].getBookingStatus()) {
                    rooms[i].bookRoom();
                    cout << "Room " << roomNumber << " booked for guest " << guestName << ".\n";
                    return;
                } else {
                    cout << "Room " << roomNumber << " is already booked.\n";
                    return;
                }
            }
        }

        cout << "Room " << roomNumber << " not found.\n";
    }

    // Release a booked room
    void releaseRoom() {
        int roomNumber;

        cout << "Enter room number to release: ";
        cin >> roomNumber;

        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].getRoomNumber() == roomNumber) {
                if (rooms[i].getBookingStatus()) {
                    rooms[i].releaseRoom();
                    cout << "Room " << roomNumber << " has been released.\n";
                    return;
                } else {
                    cout << "Room " << roomNumber << " is already available.\n";
                    return;
                }
            }
        }

        cout << "Room " << roomNumber << " not found.\n";
    }

    // Search for a guest by name
    void searchGuest() {
        string guestName;
        bool found = false;

        cout << "Enter guest name to search: ";
        cin.ignore();
        getline(cin, guestName);

        for (int i = 0; i < guestCount; i++) {
            if (guests[i].getName() == guestName) {
                cout << "Guest found:\n";
                guests[i].displayGuestDetails();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Guest " << guestName << " not found.\n";
        }
    }

    // Modify guest details
    void modifyGuest() {
        string guestName, newPhone, newAddress, newCheckIn, newCheckOut;
        bool found = false;

        cout << "Enter guest name to modify: ";
        cin.ignore();
        getline(cin, guestName);

        for (int i = 0; i < guestCount; i++) {
            if (guests[i].getName() == guestName) {
                cout << "Enter new phone number: ";
                getline(cin, newPhone);
                cout << "Enter new address: ";
                getline(cin, newAddress);
                cout << "Enter new check-in date: ";
                getline(cin, newCheckIn);
                cout << "Enter new check-out date: ";
                getline(cin, newCheckOut);
                guests[i].setGuestDetails(guestName, newPhone, newAddress, newCheckIn, newCheckOut);
                cout << "Guest details updated successfully.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Guest " << guestName << " not found.\n";
        }
    }

    // Remove a guest from the hotel
    void removeGuest() {
        string guestName;
        bool found = false;

        cout << "Enter guest name to remove: ";
        cin.ignore();
        getline(cin, guestName);

        for (int i = 0; i < guestCount; i++) {
            if (guests[i].getName() == guestName) {
                // Shift the guests to remove the specified guest
                for (int j = i; j < guestCount - 1; j++) {
                    guests[j] = guests[j + 1];
                }
                guestCount--;
                cout << "Guest " << guestName << " removed successfully.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Guest " << guestName << " not found.\n";
        }
    }

    // Display the main menu
    void displayMenu() {
        int choice;

        do {
            cout << "\n=== Hotel Management System ===\n";
            cout << "1. Add Room\n";
            cout << "2. Display Rooms\n";
            cout << "3. Search Room by Type\n";
            cout << "4. Search Room by Price\n";
            cout << "5. Add Guest\n";
            cout << "6. Display Guests\n";
            cout << "7. Book Room\n";
            cout << "8. Release Room\n";
            cout << "9. Search Guest\n";
            cout << "10. Modify Guest Details\n";
            cout << "11. Remove Guest\n";
            cout << "12. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addRoom();
                    break;
                case 2:
                    displayRooms();
                    break;
                case 3:
                    searchRoomByType();
                    break;
                case 4:
                    searchRoomByPrice();
                    break;
                case 5:
                    addGuest();
                    break;
                case 6:
                    displayGuests();
                    break;
                case 7:
                    bookRoom();
                    break;
                case 8:
                    releaseRoom();
                    break;
                case 9:
                    searchGuest();
                    break;
                case 10:
                    modifyGuest();
                    break;
                case 11:
                    removeGuest();
                    break;
                case 12:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 12);
    }
};

// Main function
int main() {
    Hotel hotel;
    hotel.displayMenu();

    return 0;
}
