#include "EconomyPassenger.h"
#include <iostream>
using namespace std;

EconomyPassenger::EconomyPassenger(int id, string n)
: Passenger(id, n) {}

double EconomyPassenger::getDiscount() const {
    return 0.05;
}

void EconomyPassenger::showDetails() const {
    cout << "Economy Passenger: " << name << endl;
}
