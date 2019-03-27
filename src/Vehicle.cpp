#include "Exceptions.h"
#include "Vehicle.h"
#include <stdexcept>
#include <iostream>
#include <math.h>

bool Vehicle::operator==(Vehicle &rhs) {
    return kLicencePlate == rhs.kLicencePlate;
}

bool Vehicle::operator!=(Vehicle &rhs) {
    return !(rhs == *this);
}

bool Vehicle::collides(Vehicle *secondCar) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    REQUIRE(secondCar != NULL, "voertuig moet bestaan");
    return collides(secondCar->getPosition(), secondCar->getCurrentRoad()->getName());
}

bool Vehicle::collides(double position, std::string roadName) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    return roadName == fCurrentRoad->getName() and this->fPosition - 5 < position and position < this->fPosition + 5;
}

unsigned int Vehicle::getSpeed() {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    return fSpeed;
}

void Vehicle::setSpeed(unsigned int speed) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    Vehicle::fSpeed = speed;
    ENSURE(speed == fSpeed, "snelheid niet aangepast");

}

unsigned int Vehicle::getPosition() {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    return fPosition;
}

void Vehicle::setPosition(unsigned int position) {
    ENSURE(position == fPosition, "positie niet aangepast");
    Vehicle::fPosition = position;
}

Road *Vehicle::getCurrentRoad() {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    return fCurrentRoad;
}

void Vehicle::setCurrentRoad(Road *currentRoad) {
    REQUIRE(currentRoad != NULL, "baan moet bestaan");
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");

    Vehicle::fCurrentRoad = currentRoad;
    ENSURE(fCurrentRoad == currentRoad, "baan niet aangepast");
}

Vehicle::Vehicle(unsigned int speed, unsigned int position, const std::string &licenePlate,
                 Road *currentRoad, VehicleType *type) : fSpeed(speed),
                                                         fPosition(position),
                                                         kLicencePlate(licenePlate),
                                                         fCurrentRoad(currentRoad), fType(type), _initCheck(this) {
    if (fCurrentRoad->getLength() < position) throw FatalException(vehicle_illegal_position);
    if (fCurrentRoad->getSpeedLimit() < speed) throw NonFatalException(vehicle_speed_error);
    if (currentRoad == 0) throw NonFatalException(vehicle_illegal_position);
    REQUIRE(currentRoad != NULL, "baan moet bestaan");
    REQUIRE(type != NULL, "type moet bestaan");
    ENSURE(properlyInitialized(), "voertuig niet goed geinitializeerd");
}

std::ostream &operator<<(std::ostream &os, Vehicle &vehicle) {
    REQUIRE(vehicle.properlyInitialized(), "voertuig niet goed geinitializeerd");
    os << "Voertuig: " << vehicle.fType->getName() << " (" + vehicle.kLicencePlate << ")" << std::endl;
    os << " --> baan    : " << vehicle.fCurrentRoad->getName() << std::endl;
    os << " --> positie : " << vehicle.fPosition << std::endl;
    os << " --> snelheid: " << vehicle.fSpeed << std::endl;
    return os;
}

bool Vehicle::setNewPosition(unsigned int timeSpent) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    fPosition += (unsigned int) round((fSpeed / 3.6) * timeSpent);
    if (fPosition > fCurrentRoad->getLength()) {
        fPosition = 0;//je moet rekening houden met de overgang naar een andere baan
        if (fCurrentRoad->getConnections().empty()) return false;
        this->setCurrentRoad(fCurrentRoad->getConnections()[0]);
        return true;
    }
    return true;
}

void Vehicle::setAcceleration(double acceleration) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    REQUIRE(acceleration <= 2, "acceleration hoger dan 2");
    REQUIRE(acceleration >= -8, " acceleration lager dan -8");
    fSpeed += (unsigned int) round(acceleration);
    if (fCurrentRoad->getSpeedLimit() < fSpeed)fSpeed = fCurrentRoad->getSpeedLimit();
}

double Vehicle::getAcceleration(std::vector<Vehicle *> vehicles) {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
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
    if (-8 >= acceleration)acceleration = -8;
    if (acceleration >= 2) acceleration = 2;
    ENSURE(acceleration <= 2, "acceleration hoger dan 2");
    ENSURE(acceleration >= -8, " acceleration lager dan -8");
    return acceleration;
}


unsigned int Vehicle::getLength() {
    REQUIRE(properlyInitialized(), "voertuig niet goed geinitializeerd");
    REQUIRE(fType != NULL, "voertuig heeft geen geldig type");

    return (unsigned int) fType->getLength();
}

Vehicle::~Vehicle() {

}

bool Vehicle::properlyInitialized() {
    return _initCheck == this;
}

void Vehicle::leaveRoad() {
    REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    fCurrentRoad = NULL;
    ENSURE(fCurrentRoad ==NULL, "voertuig heeft baan niet verlaten");
}


int VehicleType::getLength() const {
    return fLength;
}

VehicleType::VehicleType(const std::string &name) : fName(name) {
    if (name == "AUTO")fLength = 3;
    else fLength = 2;
}

std::string VehicleType::getName() {
    return fName;
}


