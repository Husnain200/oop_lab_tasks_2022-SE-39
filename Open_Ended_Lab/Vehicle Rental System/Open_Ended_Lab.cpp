#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iomanip>

// ============================================================================
// 1. VEHICLE CORE HIERARCHY
// ============================================================================
class Vehicle {
protected:
    std::string modelName;
    double baseDailyRate;
    bool rentedStatus;

public:
    Vehicle(std::string model, double rate)
        : modelName(std::move(model)), baseDailyRate(rate), rentedStatus(false) {}

    virtual ~Vehicle() = default;

    std::string getModelName() const { return modelName; }
    double getBaseRate() const { return baseDailyRate; }
    bool isCurrentlyRented() const { return rentedStatus; }
    void setRentedStatus(bool status) { rentedStatus = status; }

    // R4: Pure Virtual Method for polymorphic calculation
    virtual double calculateRentalCost(int days) const = 0;
    virtual void displaySpecs() const = 0;
};

// --- CAR SUBCLASS ---
class Car : public Vehicle {
private:
    int seatCount;

public:
    Car(std::string model, double rate, int seats)
        : Vehicle(std::move(model), rate), seatCount(seats) {}

    double calculateRentalCost(int days) const override {
        return baseDailyRate * days;
    }

    void displaySpecs() const override {
        std::cout << "Car: " << modelName << " (" << seatCount << " Seats) - $" << baseDailyRate << "/day";
    }
};

// --- MOTORBIKE SUBCLASS ---
class Motorbike : public Vehicle {
public:
    Motorbike(std::string model, double rate)
        : Vehicle(std::move(model), rate) {}

    // R4: 10% discount if rental period exceeds 7 days
    double calculateRentalCost(int days) const override {
        double cost = baseDailyRate * days;
        if (days > 7) {
            cost *= 0.90;
        }
        return cost;
    }

    void displaySpecs() const override {
        std::cout << "Motorbike: " << modelName << " - $" << baseDailyRate << "/day (10% off >7 days)";
    }
};

// --- TRUCK SUBCLASS ---
class Truck : public Vehicle {
private:
    double payloadTons;

public:
    Truck(std::string model, double rate, double payload)
        : Vehicle(std::move(model), rate), payloadTons(payload) {}

    // R4: 20% flat surcharge applied to truck rentals
    double calculateRentalCost(int days) const override {
        return (baseDailyRate * 1.20) * days;
    }

    void displaySpecs() const override {
        std::cout << "Truck: " << modelName << " (" << payloadTons << " Tons) - $" << baseDailyRate << "/day (+20% fee)";
    }
};

// ============================================================================
// 2. CUSTOMER COMPONENT
// ============================================================================
class Customer {
private:
    std::string fullName;
    std::string uniqueId;
    bool activeRentalFlag;

public:
    Customer(std::string name, std::string id)
        : fullName(std::move(name)), uniqueId(id), activeRentalFlag(false) {}

    std::string getName() const { return fullName; }
    std::string getId() const { return uniqueId; }
    bool hasActiveRental() const { return activeRentalFlag; }
    void setActiveRental(bool status) { activeRentalFlag = status; }
};

// ============================================================================
// 3. RENTAL RECORD MANAGEMENT
// ============================================================================
class RentalRecord {
private:
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Vehicle> vehicle;
    int durationDays;
    double finalCost;
    bool activeRecord;

public:
    RentalRecord(std::shared_ptr<Customer> c, std::shared_ptr<Vehicle> v, int days)
        : customer(c), vehicle(v), durationDays(days), activeRecord(true) {
        finalCost = vehicle->calculateRentalCost(durationDays);
    }

    std::shared_ptr<Customer> getCustomer() const { return customer; }
    std::shared_ptr<Vehicle> getVehicle() const { return vehicle; }
    bool isActive() const { return activeRecord; }
    
    void clearRecord() { activeRecord = false; }

    void printRow() const {
        std::cout << std::left << std::setw(12) << customer->getName()
                  << std::setw(18) << vehicle->getModelName()
                  << std::setw(8) << durationDays
                  << "$" << std::fixed << std::setprecision(2) << std::setw(10) << finalCost
                  << (activeRecord ? "[ACTIVE]" : "[CLOSED]") << "\n";
    }
};

// ============================================================================
// 4. CENTRAL CONTROLLER SYSTEM
// ============================================================================
class RentalSystem {
private:
    std::map<std::string, std::shared_ptr<Vehicle>> fleetMap;
    std::map<std::string, std::shared_ptr<Customer>> customerMap;
    std::vector<RentalRecord> globalRegistry;

public:
    void registerVehicle(const std::string& key, const std::shared_ptr<Vehicle>& vehicle) {
        fleetMap[key] = vehicle;
    }

    void registerCustomer(const std::shared_ptr<Customer>& customer) {
        customerMap[customer->getId()] = customer;
    }

    // R3: Process rental with data validations
    bool createRental(const std::string& customerId, const std::string& vehicleKey, int days) {
        auto custIt = customerMap.find(customerId);
        auto vehIt = fleetMap.find(vehicleKey);

        if (custIt == customerMap.end() || vehIt == fleetMap.end()) {
            std::cout << ">> Error: Invalid Customer ID or Vehicle lookup key.\n";
            return false;
        }

        std::shared_ptr<Customer> customer = custIt->second;
        std::shared_ptr<Vehicle> vehicle = vehIt->second;

        if (customer->hasActiveRental()) {
            std::cout << ">> Rental Rejected: " << customer->getName() << " already holds an open rental slot.\n";
            return false;
        }

        if (vehicle->isCurrentlyRented()) {
            std::cout << ">> Rental Rejected: " << vehicle->getModelName() << " is not available.\n";
            return false;
        }

        // Apply state updates
        vehicle->setRentedStatus(true);
        customer->setActiveRental(true);

        // Add history ledger record
        globalRegistry.emplace_back(customer, vehicle, days);
        std::cout << ">> Success: " << customer->getName() << " checked out " << vehicle->getModelName() << ".\n";
        return true;
    }

    // R5: Process a return operation safely
    bool acceptReturn(const std::string& vehicleKey) {
        auto vehIt = fleetMap.find(vehicleKey);
        if (vehIt == fleetMap.end()) return false;

        std::shared_ptr<Vehicle> vehicle = vehIt->second;

        for (auto& record : globalRegistry) {
            if (record.getVehicle() == vehicle && record.isActive()) {
                vehicle->setRentedStatus(false);
                record.getCustomer()->setActiveRental(false);
                record.clearRecord();
                std::cout << ">> Success: " << vehicle->getModelName() << " has been returned.\n";
                return true;
            }
        }
        std::cout << ">> Error: Match records not found for return request.\n";
        return false;
    }

    // R6: Generate systemic analytics summary data output
    void generateSystemReport() const {
        std::cout << "\n=================== SYSTEM SUMMARY REPORT ===================\n";
        std::cout << std::left << std::setw(12) << "Customer" << std::setw(18) << "Vehicle" 
                  << std::setw(8) << "Days" << std::setw(11) << "Cost" << "Status\n";
        std::cout << "-------------------------------------------------------------\n";
        
        for (const auto& record : globalRegistry) {
            if (record.isActive()) {
                record.printRow();
            }
        }

        int totalAvailable = 0, totalRented = 0;
        for (const auto& pair : fleetMap) {
            if (pair.second->isCurrentlyRented()) {
                totalRented++;
            } else {
                totalAvailable++;
            }
        }

        std::cout << "-------------------------------------------------------------\n";
        std::cout << "Metrics Dashboard: [ Available: " << totalAvailable 
                  << " Vehicles ] | [ Rented: " << totalRented << " Vehicles ]\n";
        std::cout << "=============================================================\n\n";
    }
};

// ============================================================================
// 5. DEMO ENVIRONMENT EXECUTOR
// ============================================================================
int main() {
    RentalSystem agency;

    // R1: Instantiate at least 3 distinct vehicle implementations
    auto sedan = std::make_shared<Car>("Honda Civic", 80.0, 5);
    auto cruiser = std::make_shared<Motorbike>("Harley Iron", 60.0);
    auto hauler = std::make_shared<Truck>("Volvo FH16", 200.0, 12.0);

    agency.registerVehicle("CAR01", sedan);
    agency.registerVehicle("BIKE01", cruiser);
    agency.registerVehicle("TRUCK01", hauler);

    // R2: Register sample clients
    auto user1 = std::make_shared<Customer>("John Doe", "ID-991");
    auto user2 = std::make_shared<Customer>("Jane Roe", "ID-228");
    agency.registerCustomer(user1);
    agency.registerCustomer(user2);

    std::cout << "--- Executing Initialization Sequences ---\n";

    // R3: Run 2 validation rentals
    agency.createRental("ID-991", "CAR01", 5);       // Regular base charge math
    agency.createRental("ID-228", "BIKE01", 10);     // Triggers 10% discount tier logic

    // Check system error routing (Reject duplicate vehicle allocation)
    agency.createRental("ID-991", "BIKE01", 3);

    // R6: Display system analytics snapshot
    agency.generateSystemReport();

    // R5: Perform system returns processing tasks
    std::cout << "--- Executing Core Returns Logic ---\n";
    agency.acceptReturn("CAR01");

// R6: Final report after return operation
agency.generateSystemReport();

return 0;
}
