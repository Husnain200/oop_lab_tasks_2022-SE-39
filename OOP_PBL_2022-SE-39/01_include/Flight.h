#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
using namespace std;

class Flight {

protected:
    string flightNumber;
    string origin;
    string destination;
    int totalSeats;
    int availableSeats;

public:
    Flight(string fn, string org, string dest, int total, int available);
    virtual ~Flight();
    string getFlightNumber() const;
    int getAvailableSeats() const;
    void reserveSeat();
    void releaseSeat();

    virtual double calculateBaseFare() const = 0;
    virtual void displayDetails() const = 0;
};

#endif
