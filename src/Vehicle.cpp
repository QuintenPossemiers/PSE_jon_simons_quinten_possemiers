#include "Vehicle.h"
#include <math.h>
#include <string>

const unsigned int Car::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Car::getKTypeName() {
    return "auto";
}

Car::Car(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad) : Vehicle(
        fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

}

const int Car::getKLength() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kLength;
}

const int Car::getKMinVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMinVersnelling;
}

const int Car::getKMaxVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxVersnelling;
}


unsigned int Vehicle::getFSpeed() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fSpeed;
}

unsigned int Vehicle::getFPosition() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fPosition;
}

const std::string &Vehicle::getKLicencePlate() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kLicencePlate;
}

Road *Vehicle::getFCurrentRoad() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fCurrentRoad;
}

Vehicle *Vehicle::getFPrevVehicle()  {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    return fPrevVehicle;
}

bool Vehicle::properlyInitialised() const{
    return this == _initCheck;
}

Vehicle::Vehicle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad)
        : fSpeed(fSpeed), fNoAcceleration(0), fPosition(fPosition), kLicencePlate(kLicencePlate),
          fCurrentRoad(fCurrentRoad),
          fPrevVehicle(NULL), fStroke(1), _initCheck(this) {
    REQUIRE(fCurrentRoad != NULL, "baan moet bestaan");
    if (fCurrentRoad->getLength() < fPosition) throw FatalException(vehicle_illegal_position);
    if (fCurrentRoad->getSpeedLimit(fPosition) < fSpeed) throw NonFatalException(vehicle_speed_error);
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
    return collides(secondCar->getFPosition(), secondCar->getFCurrentRoad()->getName(), secondCar->getCurrentStroke());
}

bool Vehicle::collides(double position, std::string roadName, double stroke) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return roadName == fCurrentRoad->getName() and this->fPosition - 5 - this->getKLength() < position and
           position < this->fPosition + 5 and
           (ceil(fStroke) == ceil(stroke) or floor(fStroke) == ceil(stroke) or ceil(fStroke) == floor(stroke) or
            floor(fStroke) == floor(stroke));
    //We veronderstellen dat we met de lengte rekening moeten houden
}


bool Vehicle::updatePosition() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Bus *bus = dynamic_cast<Bus *>(this);
    bool isBus = bus != NULL;
    if (isBus and bus->getTimeLeft() > 0) {
        bus->incTimeLeft();
        return true;
    }

    int updateSpeed = (int) round((fSpeed / 3.6));
    if ((unsigned int) updateSpeed > fCurrentRoad->getIsNextTrafficStop(fPosition)) {
        //throw  NonFatalException(duplicate_plate);
        //todo what to do?
    }
    fPosition += updateSpeed;
    if (fPrevVehicle != NULL and fPosition >= fPrevVehicle->getFPosition() - fPrevVehicle->getKLength() and
        fCurrentRoad == fPrevVehicle->getFCurrentRoad() and
        (ceil(fStroke) == ceil(fPrevVehicle->getCurrentStroke()) or
         ceil(fStroke) == floor(fPrevVehicle->getCurrentStroke()) or
         floor(fStroke) == floor(fPrevVehicle->getCurrentStroke()) or
         floor(fStroke) == ceil(fPrevVehicle->getCurrentStroke()))) {
        std::cout << fStroke;
        std::cout << "  \n";
        throw FatalException("fck");
    } else if (fPrevVehicle != NULL and fPosition >= fPrevVehicle->getFPosition() and
               fCurrentRoad == fPrevVehicle->getFCurrentRoad()) {
        Vehicle *x = fPrevVehicle;
        Vehicle *y = fNextVehicle;
        fPrevVehicle = x->getFPrevVehicle();
        fNextVehicle = x;
        fPrevVehicle->setFNextVehicle(this);
        if (y != NULL)
            y->setFPrevVehicle(x);
        x->setFNextVehicle(y);
        x->setFPrevVehicle(this);

    }
    if (isBus and updateSpeed == bus->getFDistanceToNextStop()) {
        bus->incTimeLeft();
    }

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

    unsigned int distToTraffic = fCurrentRoad->getIsNextTrafficStop(fPosition);
    unsigned int distToBusStop = fCurrentRoad->getNextBusStop(fPosition);
    unsigned int distToNextCar = getDistanceToNextVehicle(this);
    unsigned int closestStop = distToTraffic;
    bool sign = false;


    Bus *bus = dynamic_cast<Bus *>(this);
    bool isBus = bus != NULL;
    if (isBus and bus->getTimeLeft() != 0 and bus->getTimeLeft() != 30) {
        bus->incTimeLeft();
        this->fSpeed = 0;
        return;
    } else if (isBus and bus->getTimeLeft() == 30) {
        bus->incTimeLeft();
        fPosition += distToBusStop + 1;
    }
    if (isBus and distToTraffic > distToBusStop) closestStop = distToBusStop;
    if (isBus and distToTraffic > distToBusStop and fSpeed == 0) bus->incTimeLeft();

    double acceleration;
    double deltaIdeal = (0.75 * this->fSpeed) + getNextVehocleSize(fStroke) + 2;

    if (closestStop == (unsigned int) -1 and distToNextCar == (unsigned int) -1) {
        acceleration = getKMaxVersnelling();
    } else {
        acceleration = 0.5 * (distToNextCar - deltaIdeal);
        if (deltaIdeal * 2 > closestStop or
            (deltaIdeal == (unsigned int) -1 and closestStop == (unsigned int) -1)) {
            double stopAcc = calculateAccelerationToStopAtPosition(closestStop - fPosition);
            int distAcc = (round(closestStop * 3.6)) - fSpeed;
            if (stopAcc < acceleration) {
                acceleration = stopAcc;
                if (distAcc <= getKMinVersnelling()) {
                    acceleration = distAcc;
                    sign = true;
                }
            }
        }
    }


    if (getKMinVersnelling() >= acceleration)acceleration = getKMinVersnelling();
    if (acceleration >= getKMaxVersnelling()) acceleration = getKMaxVersnelling();
    if (fSpeed > fCurrentRoad->getSpeedLimit(fPosition)) {
        acceleration = getKMinVersnelling();
    }
    ENSURE(acceleration <= getKMaxVersnelling(), "acceleration hoger dan max versnelling");
    ENSURE(acceleration >= getKMinVersnelling(), " acceleration lager dan min versnelling");
    int lowerEnd = fCurrentRoad->getSpeedLimit(fPosition) > getKMaxSpeed() ? getKMaxSpeed() :
                   fCurrentRoad->getSpeedLimit(fPosition);

    unsigned int prevSpeed = fSpeed;
    if (lowerEnd < fSpeed + acceleration)fSpeed = lowerEnd;
    else fSpeed += (int) round(acceleration);
    if (fSpeed > 300) fSpeed = 0;
    if (prevSpeed == fSpeed)this->incAccelerationTimer();
    else resetAccelerationTimer();

    if (this->getFNoAcceleration() >= 5 and !sign and (std::string("auto") == getKTypeName() or
                                                       std::string("motorfiets") == getKTypeName()) and
        ceil(fStroke) == fStroke and getRadiusOnStroke(ceil(fStroke + 1)) >= deltaIdeal and
        fCurrentRoad->getFStrokes() >= fStroke + 1) {
        fGoingUp = true;
        fStroke += 0.2;
    } else if (this->getFNoAcceleration() >= 5 and !sign and (std::string("auto") == getKTypeName() or
                                                              std::string("motorfiets") == getKTypeName()) and
               ceil(fStroke) == fStroke and getRadiusOnStroke(ceil(fStroke - 1)) >= deltaIdeal and fStroke > 1) {
        fGoingUp = false;
        fStroke -= 0.2;
    } else if (fStroke != ceil(fStroke)) {
        fStroke += fGoingUp ? 0.2 : -0.2;
        if (fStroke - floor(fStroke) > 0.95)fStroke = floor(fStroke) + 1;
        else if (fStroke - floor(fStroke) < 0.05) fStroke = floor(fStroke);
    }



}

void Vehicle::leaveRoad() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    fCurrentRoad = NULL;
    ENSURE(getFCurrentRoad() == NULL, "voertuig heeft baan niet verlaten");
}

double Vehicle::getCurrentStroke() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fStroke;
}

double Vehicle::calculateAccelerationToStopAtPosition(int distance) {
    if (distance == 0) return -fSpeed;
    double acceleration = (-1 * (this->fSpeed * this->fSpeed)) / (double) distance;
    if (acceleration > getKMaxVersnelling())return getKMaxVersnelling();
    if (acceleration < getKMinVersnelling())return getKMinVersnelling();
    return acceleration;
}

void Vehicle::setFStroke(double stroke) {
    Vehicle::fStroke = stroke;
}

void Vehicle::resetAccelerationTimer() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    fNoAcceleration = 0;
    ENSURE(fNoAcceleration == 0, "fNoAcceleration is niet op 0 gezet");
}

void Vehicle::incAccelerationTimer() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    fNoAcceleration++;
}

int Vehicle::getDistanceToNextVehicle(Vehicle *x, bool start) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    if (fCurrentRoad == NULL) return -1;
    if ((ceil(fStroke) == ceil(x->getCurrentStroke()) or ceil(fStroke) == floor(x->getCurrentStroke()) or
         floor(fStroke) == floor(x->getCurrentStroke()) or
         floor(fStroke) == ceil(x->getCurrentStroke())) and this != x) {
        int distance = (fPosition - x->getFPosition()) - getKLength();
        Road *startingRoad = x->getFCurrentRoad();
        while (startingRoad != fCurrentRoad and startingRoad != NULL) {
            distance += startingRoad->getLength();
            if (!startingRoad->getConnections().empty()) {
                startingRoad = startingRoad->getConnections()[0];
            }
        }
        return distance;
    }

    if (fPrevVehicle == NULL)return -1;
    return fPrevVehicle->getDistanceToNextVehicle(x, false);
}

Vehicle *Vehicle::getFNextVehicle() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fNextVehicle;
}

void Vehicle::setFNextVehicle(Vehicle *NextVehicle) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Vehicle::fNextVehicle = NextVehicle;
    ENSURE(fNextVehicle== getFNextVehicle(), "nextvehicle niet aangepast");
}

void Vehicle::setFPrevVehicle(Vehicle *PrevVehicle) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Vehicle::fPrevVehicle = PrevVehicle;
    ENSURE(fPrevVehicle == getFPrevVehicle(), "fPrevVehicle niet aangepast");
}

bool Vehicle::operator<(const Vehicle &rhs) const {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    if (*rhs.getFCurrentRoad() == *fCurrentRoad and fPosition < rhs.getFPosition()) return true;
    return *fCurrentRoad > *rhs.getFCurrentRoad();
}

bool Vehicle::operator>(const Vehicle &rhs) const {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    if (*rhs.getFCurrentRoad() == *fCurrentRoad and fPosition > rhs.getFPosition()) return true;
    return *fCurrentRoad < *rhs.getFCurrentRoad();
}

bool Vehicle::operator<=(const Vehicle &rhs) const {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    return !(rhs < *this);
}

bool Vehicle::operator>=(const Vehicle &rhs) const {
    REQUIRE(properlyInitialised(),"voertuig niet goed geinitializeerd");
    return !(*this < rhs);
}

unsigned int Vehicle::getNextVehocleSize(double stroke) {
    if (ceil(fStroke) == ceil(stroke) or ceil(fStroke) == floor(stroke) or floor(fStroke) == floor(stroke) or
        floor(fStroke) == ceil(stroke))
        return getKLength();
    if (fPrevVehicle == NULL)return 0;
    return fPrevVehicle->getNextVehocleSize(stroke);

}

unsigned int Vehicle::getFNoAcceleration() const {
    return fNoAcceleration;
}

bool Vehicle::isFGoingUp()  {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fGoingUp;
}

void Vehicle::setFGoingUp(bool GoingUp) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Vehicle::fGoingUp = GoingUp;
    ENSURE(fGoingUp == isFGoingUp(), "fGoingUp niet aangepast");
}

unsigned int Vehicle::getRadiusOnStroke(int stroke) {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Vehicle *prev = fPrevVehicle;
    unsigned int radius = 0;
    while (prev != NULL) {
        if (ceil(prev->fStroke) == stroke or floor(prev->fStroke) == stroke) {
            radius = (prev->getFPosition() - fPosition);
            prev = NULL;
        } else {
            prev = prev->fPrevVehicle;
        }
    }
    if (radius == 0) radius = (unsigned int) -1;
    prev = fNextVehicle;
    while (prev != NULL) {
        if (ceil(prev->fStroke) == stroke or floor(prev->fStroke) == stroke) {
            if (radius > fPosition - prev->getFPosition())
                radius = (fPosition - prev->getFPosition());
            prev = NULL;
        } else {
            prev = prev->fNextVehicle;
        }
    }
    return radius;
}

Bus::Bus(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad) : Vehicle(
        fSpeed, fPosition, kLicencePlate, fCurrentRoad), fTimeLeft(0) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

    fDistanceToNextStop = fCurrentRoad->getNextBusStop(fPosition) - fPosition;


}

const int Bus::getKLength() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kLength;
}

const unsigned int Bus::getKMaxSpeed() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxSpeed;
}

const char *Bus::getKTypeName() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return "bus";
}

const int Bus::getKMinVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMinVersnelling;
}

const int Bus::getKMaxVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxVersnelling;
}

int Bus::getFDistanceToNextStop() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fDistanceToNextStop;
}

int Bus::getTimeLeft() const {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return fTimeLeft;
}


void Bus::incTimeLeft() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    Bus::fTimeLeft++;
    if (fTimeLeft == 31) {
        fTimeLeft = 0;
    }
    ENSURE(fTimeLeft>=0,"time left kleiner dan 0");
    //ENSURE(fTimeLeft>32,"time left groter dan 31");

}

void Bus::updateNextStop() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    fDistanceToNextStop = getFCurrentRoad()->getNextBusStop(getFPosition()) - getFPosition();
}

Truck::Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad)
        : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

}

const int Truck::getKLength() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kLength;
}

const unsigned int Truck::getKMaxSpeed() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxSpeed;
}

const char *Truck::getKTypeName() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return "vrachtwagen";
}

const int Truck::getKMinVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMinVersnelling;
}

const int Truck::getKMaxVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxVersnelling;
}

Motorcycle::Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate,
                       Road *fCurrentRoad) : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

}

const int Motorcycle::getKLength() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kLength;
}

const unsigned int Motorcycle::getKMaxSpeed() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxSpeed;
}

const char *Motorcycle::getKTypeName() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return "motorfiets";
}

const int Motorcycle::getKMinVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMinVersnelling;
}

const int Motorcycle::getKMaxVersnelling() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    return kMaxVersnelling;
}
