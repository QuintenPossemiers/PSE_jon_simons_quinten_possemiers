#include "Vehicle.h"
#include <math.h>

const int Car::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Car::getKTypeName() {
    return "auto";
}

Car::Car(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad) : Vehicle(
        fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
}

const int Car::getKLength() {
    return kLength;
}


unsigned int Vehicle::getFSpeed() const {
    return fSpeed;
}

unsigned int Vehicle::getFPosition() const {
    return fPosition;
}

const std::string &Vehicle::getKLicencePlate() const {
    return kLicencePlate;
}

Road *Vehicle::getFCurrentRoad() const {
    return fCurrentRoad;
}

Vehicle *Vehicle::getFPrevVehicle() const {
    return fPrevVehicle;
}

bool Vehicle::properlyInitialised() {
    return this == _initCheck;
}

Vehicle::Vehicle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad)
        : fSpeed(fSpeed), fPosition(fPosition), kLicencePlate(kLicencePlate), fCurrentRoad(fCurrentRoad),
          fPrevVehicle(NULL),_initCheck(this) {
    if (fCurrentRoad->getLength() < fPosition) throw FatalException(vehicle_illegal_position);
    if (fCurrentRoad->getSpeedLimit() < fSpeed) throw NonFatalException(vehicle_speed_error);
    REQUIRE(fCurrentRoad != NULL, "baan moet bestaan");
    ENSURE(properlyInitialised(), "voertuig niet goed geinitializeerd");
}

void Vehicle::setSpeed(unsigned int speed) {
    REQUIRE(properlyInitialised(), "voertuig niet goed gein_initCheck(this)itializeerd");
    Vehicle::fSpeed = speed;
    ENSURE(speed == getFSpeed(), "snelheid niet aangepast");
}

void Vehicle::setPosition(unsigned int position) {
    ENSURE(position == getFPosition(), "positie niet aangepast");
    Vehicle::fPosition = position;
}

void Vehicle::setCurrentRoad(Road *currentRoad) {
    REQUIRE(currentRoad != NULL, "baan moet bestaan");
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Vehicle::fCurrentRoad = currentRoad;
    ENSURE(getFCurrentRoad() == currentRoad, "baan niet aangepast");
}

std::ostream &operator<<(std::ostream &os, Vehicle &vehicle) {
    REQUIRE(vehicle.properlyInitialised(), "voertuig niet goed geinitializeerd");
    os << "Voertuig: " << vehicle.getKTypeName() << " (" + vehicle.kLicencePlate << ")" << std::endl;
    os << " --> baan    : " << vehicle.fCurrentRoad->getName() << std::endl;
    os << " --> positie : " << vehicle.fPosition << std::endl;
    os << " --> snelheid: " << vehicle.fSpeed << std::endl;
    return os;
}

bool Vehicle::operator==(Vehicle &rhs) {
    return kLicencePlate == rhs.kLicencePlate;
}

bool Vehicle::operator!=(Vehicle &rhs) {
    return !(rhs == *this);
}

bool Vehicle::collides(Vehicle *secondCar) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    REQUIRE(secondCar != NULL, "voertuig moet bestaan");
    return collides(secondCar->getFPosition(), secondCar->getFCurrentRoad()->getName());
}

bool Vehicle::collides(double position, std::string roadName) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return roadName == fCurrentRoad->getName() and this->fPosition - 5 - this->getKLength()< position and position < this->fPosition + 5;
    //We veronderstellen dat we met de lengte rekening moeten houden
}

bool Vehicle::setNewPosition() {
    fPosition += (unsigned int) round((fSpeed / 3.6));
    if (fPosition > fCurrentRoad->getLength()) {
        fPosition = 0;//je moet rekening houden met de overgang naar een andere baan
        if (fCurrentRoad->getConnections().empty()) return false;
        this->setCurrentRoad(fCurrentRoad->getConnections()[0]);
        return true;
    }
    return true;
}

void Vehicle::updateSpeed() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    double acceleration = 2;
    if (fPrevVehicle){

    double deltaIdeal = 0.75 * this->fSpeed + fPrevVehicle->getKLength() + 2;
    double deltaReal = fPrevVehicle->fPosition - fPrevVehicle->getKLength() - fPosition;
    acceleration = 0.5 * (deltaReal - deltaIdeal);
    if (-8 >= acceleration)acceleration = -8;
    if (acceleration >= 2) acceleration = 2;
    ENSURE(acceleration <= 2, "acceleration hoger dan 2");
    ENSURE(acceleration >= -8, " acceleration lager dan -8");
    }

    REQUIRE(acceleration <= 2, "acceleration hoger dan 2");
    REQUIRE(acceleration >= -8, " acceleration lager dan -8");
    fSpeed += (unsigned int) round(acceleration);
    if (fCurrentRoad->getSpeedLimit() < fSpeed)fSpeed = fCurrentRoad->getSpeedLimit();
    if((unsigned int)getKMaxSpeed() < fSpeed) fSpeed = (unsigned int)getKMaxSpeed();
}

void Vehicle::leaveRoad() {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    fCurrentRoad = NULL;
    ENSURE(getFCurrentRoad() ==NULL, "voertuig heeft baan niet verlaten");
}

Bus::Bus(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad) : Vehicle(
        fSpeed, fPosition, kLicencePlate, fCurrentRoad) {

}

const int Bus::getKLength() {
    return kLength;
}

const int Bus::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Bus::getKTypeName() {
    return "bus";
}

Truck::Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad)
        : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {

}

const int Truck::getKLength() {
    return kLength;
}

const int Truck::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Truck::getKTypeName() {
    return "vrachtwagen";
}

Motorcycle::Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate,
                       Road *fCurrentRoad) : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {

}

const int Motorcycle::getKLength() {
    return kLength;
}

const int Motorcycle::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Motorcycle::getKTypeName() {
    return "motorfiets";
}
