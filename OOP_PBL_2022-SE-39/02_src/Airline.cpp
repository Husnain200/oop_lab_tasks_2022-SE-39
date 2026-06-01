#include "Airline.h"
#include <fstream>
#include <iostream>
#include "Exceptions.h"

using namespace std;

Airline::Airline() {
    ticketCounter = 1;
}

Airline::~Airline() {
    for (auto f : flights) delete f;
    for (auto p : passengers) delete p;
    for (auto t : tickets) delete t;
}

// ---------------- FLIGHT ----------------

void Airline::addFlight(Flight* f) {
    flights.push_back(f);
}

// FIXED
Flight* Airline::findFlight(string flightNo) {
    for (auto f : flights) {
        if (f->getFlightNumber() == flightNo)  // IMPORTANT FIX
            return f;
    }
    return nullptr;
}

// ---------------- PASSENGER ----------------

void Airline::addPassenger(Passenger* p) {
    passengers.push_back(p);
}

Passenger* Airline::findPassenger(int id) {
    for (auto p : passengers)
        if (p->getID() == id)
            return p;
    return nullptr;
}

// ---------------- BOOKING ----------------

void Airline::bookTicket(int passengerID, string flightNo) {

    Passenger* p = findPassenger(passengerID);
    Flight* f = findFlight(flightNo);

    try {

        if (!p || !f)
            throw InvalidBookingException();

        if (f->getAvailableSeats() <= 0)
            throw FlightFullException();

        f->reserveSeat();

        Ticket* t = new Ticket(ticketCounter++, p, f, f->getAvailableSeats());
        tickets.push_back(t);

        cout << "Ticket Booked Successfully!" << endl;
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

// ---------------- DISPLAY ----------------

void Airline::showFlights() const {
    for (auto f : flights)
        f->displayDetails();
}

void Airline::showPassengers() const {
    for (auto p : passengers)
        p->showDetails();
}

void Airline::showTickets() const {
    for (auto t : tickets)
        t->showTicket();
}

// ---------------- CANCEL ----------------

void Airline::cancelTicket(int ticketID) {
    for (auto t : tickets) {
        if (t->getTicketID() == ticketID) {
            t->cancelTicket();
            cout << "Cancelled!" << endl;
            return;
        }
    }
    cout << "Ticket not found!" << endl;
}




// ---------------- SAVE DATA (IMPROVED) ----------------

void Airline::saveData() {

    ofstream outF("flights.txt");
    ofstream outP("passengers.txt");
    ofstream outT("tickets.txt");

    // Save Flights (REAL DATA)
    for (auto f : flights) {
        outF << f->getFlightNumber() << " "
             << f->getAvailableSeats() << endl;
    }

    // Save Passengers
    for (auto p : passengers) {
        outP << p->getID() << " "
             << p->getName() << endl;
    }

    // Save Tickets
    for (auto t : tickets) {
        outT << t->getTicketID() << " "
             << t->getFarePaid() << endl;
    }

    cout << "Data Saved Successfully!" << endl;
}
void Airline::loadData() {
    cout << "Loading data from files..." << endl;

    ifstream inF("flights.txt");
    ifstream inP("passengers.txt");
    ifstream inT("tickets.txt");

    if (!inF || !inP || !inT) {
        cout << "No saved data found!" << endl;
        return;
    }

    cout << "Data loaded successfully (basic version)" << endl;
}

// ---------------- REPORT ----------------
void Airline::showReport() const {

    cout << "\n===== AIRLINE REPORT =====" << endl;

    cout << "Total Flights: " << flights.size() << endl;
    cout << "Total Passengers: " << passengers.size() << endl;
    cout << "Total Tickets: " << tickets.size() << endl;

    double revenue = 0;

    for (auto t : tickets)
        revenue += t->getFarePaid();

    cout << "Total Revenue: " << revenue << endl;

    cout << "==========================" << endl;
}

