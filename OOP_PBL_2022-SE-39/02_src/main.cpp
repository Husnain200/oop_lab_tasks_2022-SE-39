#include <iostream>
#include "Airline.h"
#include "DomesticFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "FirstClassPassenger.h"

using namespace std;

int main() {

    Airline airline;

    airline.loadData();   // ? correct placement (at start)

    int choice;

    while (true) {

        cout << "\n===== AIRLINE RESERVATION SYSTEM =====" << endl;
        cout << "1. Add Flight" << endl;
        cout << "2. Add Passenger" << endl;
        cout << "3. Book Ticket" << endl;
        cout << "4. Show Flights" << endl;
        cout << "5. Show Passengers" << endl;
        cout << "6. Show Tickets" << endl;
        cout << "7. Cancel Ticket" << endl;
        cout << "8. Report" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

if(cin.fail()) {

    cin.clear();

    cin.ignore(1000, '\n');

    cout << "Invalid Input! Enter numbers only." << endl;

    continue;
}

        if (choice == 0) {
    airline.saveData();
    cout << "Data Saved Successfully!" << endl;
    break;
}

        switch (choice) {

        case 1: {
            string fn, org, dest;
            int total, available;
            double tax;

            cout << "Enter Flight No: ";
            cin >> fn;
            cout << "Origin: ";
            cin >> org;
            cout << "Destination: ";
            cin >> dest;
            cout << "Total Seats: ";
            cin >> total;
            if(total <= 0) {
    cout << "Invalid seats!" << endl;
    break;
}
            cout << "Available Seats: ";
            cin >> available;
            cout << "Tax: ";
            cin >> tax;

            airline.addFlight(new DomesticFlight(fn, org, dest, total, available, tax));
            cout << "Flight Added!" << endl;
            break;
        }

        case 2: {
            int id, type;
            string name;

            cout << "Enter ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> name;

            cout << "Type (1-Eco, 2-Business, 3-First): ";
            cin >> type;

            if (type == 1)
                airline.addPassenger(new EconomyPassenger(id, name));
            else if (type == 2)
                airline.addPassenger(new BusinessPassenger(id, name));
            else
                airline.addPassenger(new FirstClassPassenger(id, name));

            cout << "Passenger Added!" << endl;
            break;
        }

        case 3: {
            int pid;
            string flightNo;

            cout << "Enter Passenger ID: ";
            cin >> pid;
            cout << "Enter Flight No: ";
            cin >> flightNo;

            airline.bookTicket(pid, flightNo);
            break;
        }

        case 4:
            airline.showFlights();
            break;

        case 5:
            airline.showPassengers();
            break;

        case 6:
            airline.showTickets();
            break;

        case 7: {
            int tid;
            cout << "Enter Ticket ID: ";
            cin >> tid;
            airline.cancelTicket(tid);
            break;
        }

        case 8:
            airline.showReport();
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }
    }

    cout << "System Closed." << endl;

    return 0;
}
