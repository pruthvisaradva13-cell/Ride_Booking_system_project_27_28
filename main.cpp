#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;


// VERSION 1: MVP (Single-File Implementation)

class RideBooking {
private:
    int bookingID;
    string passengerName;
    string phone;
    string pickup;
    string destination;
    string vehicle;
    string payment;
    string status;
    string driverName;
    string driverPhone;
    double distance;
    double fare;

public:
    // Constructor
    RideBooking() {
        bookingID = 0;
        distance = 0.0;
        fare = 0.0;
        status = "Not Booked";
        vehicle = "None";
        payment = "None";
    }

    // 1. Passenger Registration
    void registerPassenger() {
        cout << "\n--- Passenger Registration ---\n";
        while (true) {
            cout << "Enter Name: ";
            getline(cin, passengerName);
            if (!passengerName.empty()) break;
            cout << "Name cannot be empty. Try again.\n";
        }

        while (true) {
            cout << "Enter Phone (10 digits): ";
            getline(cin, phone);
            if (phone.length() == 10) break;
            cout << "Phone must be exactly 10 characters. Try again.\n";
        }
        cout << "Registration Successful!\n";
    }

    // 2. Show Vehicles & Rates
    void showVehicles() {
        cout << "\n--- Available Vehicles & Rates (per km) ---\n";
        cout << "1. Bike      - Rs. 8\n";
        cout << "2. Auto      - Rs. 12\n";
        cout << "3. Mini Car  - Rs. 15\n";
        cout << "4. Sedan     - Rs. 20\n";
        cout << "5. SUV       - Rs. 25\n";
    }

    // 3. Get Rate based on choice
    double getRate(int choice) {
        switch (choice) {
            case 1: vehicle = "Bike"; return 8.0;
            case 2: vehicle = "Auto"; return 12.0;
            case 3: vehicle = "Mini Car"; return 15.0;
            case 4: vehicle = "Sedan"; return 20.0;
            case 5: vehicle = "SUV"; return 25.0;
            default: return 0.0;
        }
    }

    // 4. Assign Driver (Simulated)
    void getDriver() {
        if (vehicle == "Bike") { driverName = "Raju"; driverPhone = "9876543210"; }
        else if (vehicle == "Auto") { driverName = "Suresh"; driverPhone = "9876543211"; }
        else if (vehicle == "Mini Car") { driverName = "Amit"; driverPhone = "9876543212"; }
        else if (vehicle == "Sedan") { driverName = "Vikram"; driverPhone = "9876543213"; }
        else { driverName = "Rahul"; driverPhone = "9876543214"; }
    }

    // 5. Estimate Fare
    void estimateFare() {
        int choice;
        showVehicles();
        cout << "Select Vehicle (1-5): ";
        cin >> choice;
        
        double rate = getRate(choice);
        if (rate == 0.0) {
            cout << "Invalid vehicle choice.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Distance (km): ";
        cin >> distance;
        if (distance <= 0) {
            cout << "Distance must be positive.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        fare = distance * rate;
        cout << "Estimated Fare for " << vehicle << " (" << distance << " km): Rs. " << fare << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // 6. Book Ride
    void bookRide() {
        if (status == "Booked" || status == "Ongoing") {
            cout << "Cannot book. A ride is already " << status << ".\n";
            return;
        }

        cout << "\n--- Book a Ride ---\n";
        cout << "Enter Pickup Location: ";
        getline(cin, pickup);
        cout << "Enter Destination: ";
        getline(cin, destination);

        if (pickup.empty() || destination.empty() || pickup == destination) {
            cout << "Invalid locations. Pickup and Destination must be different and non-empty.\n";
            return;
        }

        int choice;
        showVehicles();
        cout << "Select Vehicle (1-5): ";
        cin >> choice;

        double rate = getRate(choice);
        if (rate == 0.0) {
            cout << "Invalid vehicle choice.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Estimated Distance (km): ";
        cin >> distance;
        if (distance <= 0) {
            cout << "Distance must be positive.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        fare = distance * rate;

        int payChoice;
        cout << "Select Payment Method:\n1. Cash\n2. UPI\n3. Card\nChoice: ";
        cin >> payChoice;
        if (payChoice == 1) payment = "Cash";
        else if (payChoice == 2) payment = "UPI";
        else if (payChoice == 3) payment = "Card";
        else {
            cout << "Invalid payment method.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Assign ID and Driver
        static int nextID = 1001;
        bookingID = nextID++;
        getDriver();
        status = "Booked";

        cout << "\n=== Booking Confirmed ===\n";
        showRideDetails();
        saveBooking();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // 7. Show Ride Details
    void showRideDetails() {
        if (bookingID == 0) {
            cout << "No active booking.\n";
            return;
        }
        cout << "Booking ID: " << bookingID << "\n";
        cout << "Passenger: " << passengerName << " (" << phone << ")\n";
        cout << "Route: " << pickup << " -> " << destination << "\n";
        cout << "Vehicle: " << vehicle << " | Driver: " << driverName << " (" << driverPhone << ")\n";
        cout << "Distance: " << distance << " km | Fare: Rs. " << fare << "\n";
        cout << "Payment: " << payment << " | Status: " << status << "\n";
        cout << "=========================\n";
    }

    // 8. Start Ride
    void startRide() {
        if (status != "Booked") {
            cout << "Cannot start. Current status: " << status << "\n";
            return;
        }
        status = "Ongoing";
        cout << "Ride Started!\n";
        saveBooking();
    }

    // 9. Complete Ride
    void completeRide() {
        if (status != "Ongoing") {
            cout << "Cannot complete. Current status: " << status << "\n";
            return;
        }
        status = "Completed";
        cout << "Ride Completed!\n";
        saveBooking();
        generateBill();
    }

    // 10. Cancel Ride
    void cancelRide() {
        if (status != "Booked") {
            cout << "Cannot cancel. Current status: " << status << "\n";
            return;
        }
        char confirm;
        cout << "Confirm cancellation? (Y/N): ";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (confirm == 'Y' || confirm == 'y') {
            status = "Cancelled";
            cout << "Ride Cancelled.\n";
            saveBooking();
        } else {
            cout << "Cancellation aborted.\n";
        }
    }

    // 11. Generate Bill
    void generateBill() {
        ofstream billFile("RideBill.txt");
        if (!billFile.is_open()) {
            cout << "Error opening RideBill.txt\n";
            return;
        }
        billFile << "========= RIDE BILL =========\n";
        billFile << "Booking ID: " << bookingID << "\n";
        billFile << "Passenger: " << passengerName << "\n";
        billFile << "Route: " << pickup << " to " << destination << "\n";
        billFile << "Distance: " << distance << " km\n";
        billFile << "Vehicle: " << vehicle << "\n";
        billFile << "Payment: " << payment << "\n";
        billFile << "Total Fare: Rs. " << fare << "\n";
        billFile << "=============================\n";
        billFile.close();
        cout << "Bill saved to RideBill.txt\n";
    }

    // 12. Save Booking to History
    void saveBooking() {
        ofstream historyFile("RideHistory.txt", ios::app);
        if (!historyFile.is_open()) return;
        
        historyFile << "ID: " << bookingID 
                    << " | " << passengerName 
                    << " | " << pickup << "->" << destination 
                    << " | " << vehicle 
                    << " | " << distance << "km" 
                    << " | Rs." << fare 
                    << " | " << payment 
                    << " | " << status << "\n";
        historyFile.close();
    }

    // 13. View History
    void viewHistory() {
        ifstream historyFile("RideHistory.txt");
        if (!historyFile.is_open()) {
            cout << "No history found.\n";
            return;
        }
        cout << "\n--- Ride History ---\n";
        string line;
        while (getline(historyFile, line)) {
            cout << line << "\n";
        }
        historyFile.close();
    }
};

// ==========================================
// MAIN FUNCTION (Menu-Driven Logic)
// ==========================================
int main() {
    RideBooking ride;
    int choice;
    bool registered = false;

    cout << "==========================================\n";
    cout << "   ONLINE RIDE BOOKING SYSTEM (Group 13)   \n";
    cout << "==========================================\n";

    // Registration Loop
    while (!registered) {
        cout << "\n1. Register Passenger\n2. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) {
            ride.registerPassenger();
            registered = true;
        } else if (choice == 2) {
            cout << "Exiting...\n";
            return 0;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    // Main Menu Loop
    do {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Estimate Fare\n";
        cout << "2. Book a Ride\n";
        cout << "3. View Ride Details\n";
        cout << "4. Start Ride\n";
        cout << "5. Complete Ride\n";
        cout << "6. Cancel Ride\n";
        cout << "7. View History\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: ride.estimateFare(); break;
            case 2: ride.bookRide(); break;
            case 3: ride.showRideDetails(); break;
            case 4: ride.startRide(); break;
            case 5: ride.completeRide(); break;
            case 6: ride.cancelRide(); break;
            case 7: ride.viewHistory(); break;
            case 8: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
