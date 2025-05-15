#include "Factory.h"

Factory::Factory(int cap) : capacity(cap), count(0) {
    vehicles = new Vehicle*[capacity];
}

Factory::~Factory() {
    for (int i = 0; i < count; i++) {
        delete vehicles[i];
    }
    delete[] vehicles;
}

void Factory::addVehicle(Vehicle* vehicle) {
    // To do3: Implement the addVehicle function
    if (count < capacity) {
        // Check if array is full
        // Add vehicle to array
        vehicles[count++] = vehicle;
    } else {
        cout << "Factory is full, cannot add more vehicles!" << endl;
    }
}

void Factory::listAllVehicles() const {
// To do3: Implement the listAllVehicles function
    for (int i = 0; i < count; i++) {
        // Vehicle *vehicle = vehicles[i];
        vehicles[i]->displayInfo();
    }
}

void Factory::listCombustionVehicles() const {
    for (int i = 0; i < count; i++) {
        if (dynamic_cast<CombustionVehicle*>(vehicles[i])) {
            vehicles[i]->displayInfo();
        }
    }
}

void Factory::listElectricVehicles() const {
    for (int i = 0; i < count; i++) {
        if (dynamic_cast<ElectricVehicle*>(vehicles[i])) {
            vehicles[i]->displayInfo();
        }
    }
}

double Factory::calculateTotalCombustionCost() const {
    double totalCost = 0.0;
    for (int i = 0; i < count; i++) {
        if (dynamic_cast<CombustionVehicle*>(vehicles[i])) {
            totalCost += vehicles[i]->calculateCost();
        }
    }
    return totalCost;
}

double Factory::calculateTotalElectricCost() const {
    double totalCost = 0.0;
    for (int i = 0; i < count; i++) {
        if (dynamic_cast<ElectricVehicle*>(vehicles[i])) {
            totalCost += vehicles[i]->calculateCost();
        }
    }
    return totalCost;
}

double Factory::calculateTotalCost() const {
// Todo3: Implement the calculateTotalCost function
    double totalCost = 0.0;
    for (int i = 0; i < count; i++) {
        totalCost += vehicles[i]->calculateCost();
    }
    return totalCost;
} 