#ifndef AIRLINE_H
#define AIRLINE_H
#include <fstream>
#include <iostream>
#include <vector>
#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"

using namespace std;

class Airline {

private:
    vector<Flight*> flights;
    vector<Passenger*> passengers;
    vector<Ticket*> tickets;
    int ticketCounter;

public:
    Airline();
    ~Airline();

    void addFlight(Flight* f);
    void addPassenger(Passenger* p);

    Flight* findFlight(string flightNo);
    Passenger* findPassenger(int id);

    void bookTicket(int passengerID, string flightNo);

    void showFlights() const;
    void showPassengers() const;
    void showTickets() const;

    void cancelTicket(int ticketID);

    void showReport() const;
    void saveData();
     void loadData();
     
};

#endif
