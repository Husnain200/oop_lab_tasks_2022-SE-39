#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
using namespace std;

// ?? Exception 1: Flight Full
class FlightFullException : public exception {
public:
    const char* what() const noexcept override {
        return "Flight is FULL! Cannot book ticket.";
    }
};

// ?? Exception 2: Invalid Booking
class InvalidBookingException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid booking request!";
    }
};

#endif
