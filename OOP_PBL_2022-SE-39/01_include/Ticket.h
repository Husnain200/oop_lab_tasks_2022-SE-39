#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include "Passenger.h"
#include "Flight.h"

using namespace std;

class Ticket {

private:
    int ticketID;
    Passenger* passenger;
    Flight* flight;
    int seatNumber;
    double farePaid;
    bool isCancelled;
friend ostream& operator<<(ostream& out, const Ticket& t);
public:
    Ticket(int id, Passenger* p, Flight* f, int seat);
    
    int getTicketID() const;
    double getFarePaid() const;
    bool getStatus() const;

    void calculateFare();
    void cancelTicket();

    void showTicket() const;

    bool operator==(const Ticket& other) const;
};

#endif
