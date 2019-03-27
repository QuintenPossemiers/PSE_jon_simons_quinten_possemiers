#include "Exeptions/Exceptions.h"
#include "Vehicle.h"
#include <stdexcept>
#include <iostream>
#include <math.h>

bool Vehicle::operator==(const Vehicle &rhs) const {
    return kLicencePlate == rhs.kLicencePlate;
}

bool Vehicle::operator!=(const Vehicle &rhs) const {
    return !(rhs == *this);
}

bool Vehicle::collides(Vehicle *secondCar) {
    return collides(secondCar->getPosition(), secondCar->getCurrentRoad()->getName());
}

bool Vehicle::collides(double position, std::string roadName) {
    return roadName == fCurrentRoad->getName() and this->fPosition - 5 < position and position < this->fPosition + 5;
}

unsigned int Vehicle::getSpeed() const {
    return fSpeed;
}

void Vehicle::setSpeed(unsigned int speed) {
    Vehicle::fSpeed = speed;
}

unsigned int Vehicle::getPosition() const {
    return fPosition;
}

void Vehicle::setPosition(unsigned int position) {
    Vehicle::fPosition = position;
}

const std::string &Vehicle::getLicencePlate() const {
    return kLicencePlate;
}

Road *Vehicle::getCurrentRoad() const {
    return fCurrentRoad;
}

void Vehicle::setCurrentRoad(Road *currentRoad) {
    Vehicle::fCurrentRoad = currentRoad;
}

Vehicle::Vehicle(unsigned int speed, unsigned int position, const std::string &licenePlate,
                 Road *currentRoad, VehicleType *type) : fSpeed(speed),
                                                          fPosition(position),
                                                          kLicencePlate(licenePlate),
                                                          fCurrentRoad(currentRoad), fType(type), _initCheck(this) {

    if (fCurrentRoad->getLength() < position) throw FatalException(vehicle_illegal_position);
    if (fCurrentRoad->getSpeedLimit() < speed) throw NonFatalException(vehicle_speed_error);
    if (currentRoad == 0) throw NonFatalException(vehicle_illegal_position);
}

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
    os << "Voertuig: " << vehicle.fType->getName() << " (" + vehicle.kLicencePlate << ")" << std::endl;
    os << " --> baan    : " << vehicle.fCurrentRoad->getName() << std::endl;
    os << " --> positie : " << vehicle.fPosition << std::endl;
    os << " --> snelheid: " << vehicle.fSpeed << std::endl;
    return os;
}

bool Vehicle::setNewPosition(unsigned int timeSpent) {
    fPosition += (unsigned int)round((fSpeed / 3.6) * timeSpent);
    if (fPosition > fCurrentRoad->getLength()) {
        fPosition = 0;//je moet rekening houden met de overgang naar een andere baan
        if (fCurrentRoad->getConnections().empty()) return false;
        this->setCurrentRoad(fCurrentRoad->getConnections()[0]);
        return true;
    }
    return true;
}

void Vehicle::setAcceleration(double acceleration) {
    fSpeed += (unsigned int)round(acceleration);
    if (fSpeed > 150)fSpeed = 150;
    if (fCurrentRoad->getSpeedLimit() < fSpeed)fSpeed = fCurrentRoad->getSpeedLimit();
}

double Vehicle::getAcceleration(std::vector<Vehicle *> vehicles) {
    Vehicle *previousVehicle = NULL;
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        if (this != vehicles[i] and previousVehicle) {
            if (vehicles[i]->fPosition > fPosition and previousVehicle->fPosition > vehicles[i]->fPosition)
                previousVehicle = vehicles[i];
        } else if (this != vehicles[i] and vehicles[i]->fPosition > fPosition) {
            previousVehicle = vehicles[i];
        }
    }

    if (!previousVehicle) return 2;

    double deltaIdeal = 0.75 * this->fSpeed + previousVehicle->getLength() + 2;
    double deltaReal = previousVehicle->fPosition - previousVehicle->getLength() - fPosition;
    double acceleration = 0.5 * (deltaReal - deltaIdeal);
    if (-8 >= acceleration)return -8;
    if (acceleration >= 2) return 2;
    return acceleration;
}


unsigned int Vehicle::getLength() const {
    return (unsigned int)fType->getLength();
}

Vehicle::~Vehicle() {

}

bool Vehicle::properlyInitialized() {
    return _initCheck == this;
}


int VehicleType::getLength() const {
    return fLength;
}

VehicleType::VehicleType(const std::string &name) : fName(name) {
    if (name == "AUTO")fLength = 3;
}

std::string VehicleType::getName() {
    return fName;
}


