#include "BusinessPassenger.h"
#include <iostream>
using namespace std;

BusinessPassenger::BusinessPassenger(int id, string n)
: Passenger(id, n) {}

double BusinessPassenger::getDiscount() const {
    return 0.10;
}

void BusinessPassenger::showDetails() const {
    cout << "Business Passenger: " << name << endl;
}
