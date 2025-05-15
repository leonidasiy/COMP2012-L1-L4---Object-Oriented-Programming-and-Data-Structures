#include "parking_lot.h"
#include <iostream>

ParkingLot::ParkingLot(const string& name, int capacity) {
    // TODO 1: ParkingLot constructor
    this->name = name;
    cout << "[Creation] Parking Lot " << name << endl;
    this->capacity = capacity;
    num_of_spots = 0;
    spots = new ParkingSpot*[capacity];
    for (int i = 0; i < capacity; ++i) {
        spots[i] = nullptr;
    }
}

ParkingLot::ParkingLot(const ParkingLot& lot) {
    // TODO 2: ParkingLot copy constructor
    this->name = lot.name;
    cout << "[CopyCreation] Parking Lot " << name << endl;
    this->capacity = lot.capacity;
    num_of_spots = 0;
    spots = new ParkingSpot*[capacity];
    for (int i = 0; i < capacity; ++i) {
        spots[i] = nullptr;
        if (lot.spots[i]) {
            createSpot(lot.spots[i]->getSpotNumber(), lot.spots[i]->getVehicle());
        }
    }
}

ParkingLot::~ParkingLot() {
    // TODO 3: ParkingLot destructor
    cout << "[Destructor] Parking Lot " << name << endl;
    for (int i = 0; i < num_of_spots; ++i) {
        if (spots[i]) {
            delete spots[i];
        }
    }
    delete[] spots;
}

void ParkingLot::createSpot(const string& spotNumber, Vehicle* vehicle) {
    if (num_of_spots >= capacity) {
        cout << "Cannot create more spots. Parking lot is at capacity." << endl;
        return;
    }
    
    spots[num_of_spots++] = new ParkingSpot(spotNumber, vehicle);
}

bool ParkingLot::addVehicle(Vehicle* vehicle, const string& spotNumber) {
    // TODO 4: addVehicle member function in parkingLot class
    if (vehicle) {
        for (int i = 0; i < num_of_spots; ++i) {
            // cout << i;
            // if (!spots[i]) {
            //     continue;
            // }
            if (spots[i]->isOccupied()) {
                if (spots[i]->getVehicle() == vehicle) {
                    cout << "Vehicle " << spots[i]->getVehicle()->getLicensePlate() << " is already parked in spot " << spots[i]->getSpotNumber() << "." << endl;
                    return false;
                }
                if (spots[i]->getSpotNumber() == spotNumber) {
                    cout << "Spot " << spotNumber << " is already occupied." << endl;
                    return false;
                }
            } else {
                if (spots[i]->getSpotNumber() == spotNumber) {
                    return spots[i]->parkVehicle(vehicle);
                }
            }
        }
        cout << "Spot " << spotNumber << " not found in " << name << endl;
        return false;
    }
    cout << "Invalid vehicle." << endl;
    return false;
}

bool ParkingLot::removeVehicle(const string& spotNumber) {
    for (int i = 0; i < num_of_spots; i++) {
        if (spots[i] != nullptr && spots[i]->getSpotNumber() == spotNumber) {
            if (!spots[i]->isOccupied()) {
                cout << "Spot " << spotNumber << " is already empty." << endl;
                return false;
            }
            spots[i]->removeVehicle();
            return true;
        }
    }
    cout << "Spot " << spotNumber << " not found in " << name << endl;
    return false;
}

string ParkingLot::getName() const {
    return name;
}

void ParkingLot::setName(const string& lotName) {
    name = lotName;
}

void ParkingLot::display() const {
    cout << "========================================" << endl; 
    cout << "Parking Lot " << name << endl;
    for (int i = 0; i < num_of_spots; i++) {
        if (spots[i] != nullptr) {
            cout << i << ". " << spots[i]->getSpotNumber();
            if (spots[i]->isOccupied()) {
                cout << " - " << spots[i]->getVehicle()->getLicensePlate();
            } else {
                cout << " - Empty";
            }
            cout << endl;
        }
    }
    cout << "========================================" << endl;
}
