#include "FirstClassPassenger.h"
#include <iostream>
using namespace std;

FirstClassPassenger::FirstClassPassenger(int id, string n)
: Passenger(id, n) {}

double FirstClassPassenger::getDiscount() const {
    return 0.20;
}

void FirstClassPassenger::showDetails() const {
    cout << "First Class Passenger: " << name << endl;
}
