#include "Flight.h"

Flight::Flight(string fn, string org, string dest, int total, int available) {
    flightNumber = fn;
    origin = org;
    destination = dest;
    totalSeats = total;
    availableSeats = available;
}

Flight::~Flight() {}

int Flight::getAvailableSeats() const {
    return availableSeats;
}

void Flight::reserveSeat() {
    if (availableSeats > 0)
        availableSeats--;
}

void Flight::releaseSeat() {
    availableSeats++;
}
string Flight::getFlightNumber() const {
    return flightNumber;
}
