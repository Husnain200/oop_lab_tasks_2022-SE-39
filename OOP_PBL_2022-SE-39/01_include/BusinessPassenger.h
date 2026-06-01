#ifndef BUSINESSPASSENGER_H
#define BUSINESSPASSENGER_H

#include "Passenger.h"

class BusinessPassenger : public Passenger {

public:
    BusinessPassenger(int id, string n);

    double getDiscount() const override;
    void showDetails() const override;
};

#endif
