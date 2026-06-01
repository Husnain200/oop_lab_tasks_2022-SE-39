#include "DomesticFlight.h"
#include <iostream>
using namespace std;

DomesticFlight::DomesticFlight(string fn, string org, string dest, int total, int available, double t)
: Flight(fn, org, dest, total, available) {
    tax = t;
}

double DomesticFlight::calculateBaseFare() const {
    return 15000 + tax;
}

void DomesticFlight::displayDetails() const {
    cout << "Flight: " << flightNumber << endl;
    cout << "From: " << origin << endl;
    cout << "To: " << destination << endl;
    cout << "Seats: " << availableSeats << endl;
}
