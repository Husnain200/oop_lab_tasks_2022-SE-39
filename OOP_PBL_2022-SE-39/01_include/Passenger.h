#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
using namespace std;

class Passenger {

protected:
    int passengerID;
    string name;

public:
    Passenger(int id, string n);
    virtual ~Passenger();

    int getID() const;
    string getName() const;

    virtual double getDiscount() const = 0;
    virtual void showDetails() const = 0;
};

#endif
