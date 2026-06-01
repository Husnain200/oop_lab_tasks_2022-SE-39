#ifndef ECONOMYPASSENGER_H
#define ECONOMYPASSENGER_H

#include "Passenger.h"

class EconomyPassenger : public Passenger {

public:
    EconomyPassenger(int id, string n);

    double getDiscount() const override;
    void showDetails() const override;
};

#endif
