#ifndef FIRSTCLASSPASSENGER_H
#define FIRSTCLASSPASSENGER_H

#include "Passenger.h"

class FirstClassPassenger : public Passenger {

public:
    FirstClassPassenger(int id, string n);

    double getDiscount() const override;
    void showDetails() const override;
};

#endif
