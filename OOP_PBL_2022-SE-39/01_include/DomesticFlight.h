#ifndef DOMESTICFLIGHT_H
#define DOMESTICFLIGHT_H

#include "Flight.h"

class DomesticFlight : public Flight {

private:
    double tax;

public:
    DomesticFlight(string fn, string org, string dest, int total, int available, double t);

    double calculateBaseFare() const override;
    void displayDetails() const override;
};

#endif
