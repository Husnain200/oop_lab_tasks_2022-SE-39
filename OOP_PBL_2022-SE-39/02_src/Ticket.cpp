#include "Ticket.h"
#include <iostream>
using namespace std;

Ticket::Ticket(int id, Passenger* p, Flight* f, int seat) {
    ticketID = id;
    passenger = p;
    flight = f;
    seatNumber = seat;
    isCancelled = false;

    calculateFare();
}

int Ticket::getTicketID() const {
    return ticketID;
}

double Ticket::getFarePaid() const {
    return farePaid;
}

bool Ticket::getStatus() const {
    return isCancelled;
}

void Ticket::calculateFare() {
    farePaid = flight->calculateBaseFare() -
              (flight->calculateBaseFare() * passenger->getDiscount());
}

void Ticket::cancelTicket() {
    isCancelled = true;
    flight->releaseSeat();
}

void Ticket::showTicket() const {
    cout << "\nTicket ID: " << ticketID << endl;
    cout << "Passenger: " << passenger->getName() << endl;
    cout << "Seat: " << seatNumber << endl;
    cout << "Fare: " << farePaid << endl;
}

bool Ticket::operator==(const Ticket& other) const {
    return ticketID == other.ticketID;
}


ostream& operator<<(ostream& out, const Ticket& t) {
    out << "===== TICKET INFO =====" << endl;
    out << "Ticket ID: " << t.ticketID << endl;
    out << "Fare Paid: " << t.farePaid << endl;
    out << "Seat Number: " << t.seatNumber << endl;
    out << "Status: " << (t.isCancelled ? "Cancelled" : "Active") << endl;
    return out;
}
