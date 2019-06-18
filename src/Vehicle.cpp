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
    return kLength;
}

const int Car::getKMinVersnelling() {
    return kMinVersnelling;
}

const int Car::getKMaxVersnelling() {
    return kMaxVersnelling;
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
          fPrevVehicle(NULL), fStroke(1), _initCheck(this) {
    if (fCurrentRoad->getLength() < fPosition) throw FatalException(vehicle_illegal_position);
    if (fCurrentRoad->getSpeedLimit(fPosition) < fSpeed) throw NonFatalException(vehicle_speed_error);
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
    if ((unsigned int)updateSpeed > fCurrentRoad->getIsNextTrafficStop(fPosition)){
        //throw  NonFatalException(duplicate_plate);
        //todo what to do?
    }
    fPosition += updateSpeed;
<<<<<<< HEAD
    if (isBus and (unsigned)updateSpeed == (unsigned )bus->getFDistanceToNextStop()) {
=======
    if (fPrevVehicle != NULL and fPosition >= fPrevVehicle->getFPosition() - fPrevVehicle->getKLength() and
        fCurrentRoad == fPrevVehicle->getFCurrentRoad()) {
        std::cout << fSpeed << " " << fPosition << " " << fStroke << " " << fPrevVehicle << " "
                  << fCurrentRoad->getName() << "\n";
        std::cout << fPrevVehicle->getFSpeed() << " " << fPrevVehicle->fPosition << " " << fPrevVehicle->fStroke << " "
                  << fPrevVehicle->fCurrentRoad->getName();
        std::cout << "  \n";
        throw FatalException("fck");
    }
    if (isBus and updateSpeed == bus->getFDistanceToNextStop()) {
>>>>>>> aa03174890ba258624990fd9ba2f1178ce5e2456
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

    Bus *bus = dynamic_cast<Bus *>(this);
    bool isBus = bus != NULL;
    if (isBus and bus->getTimeLeft() != 0) {
        bus->incTimeLeft();
        this->fSpeed = 0;
        return;
    }
    if (isBus and distToTraffic > distToBusStop) closestStop = distToBusStop;

    double acceleration;
    double deltaIdeal = (0.75 * this->fSpeed) + getNextVehocleSize(fStroke) + 2;

    if (closestStop == (unsigned int) -1 and distToNextCar == (unsigned int) -1) {
        acceleration = getKMaxVersnelling();
    } else {
        acceleration = 0.5 * (distToNextCar - deltaIdeal);
        if (deltaIdeal * 2 > closestStop or
            (deltaIdeal == (unsigned int) -1 and closestStop == (unsigned int) -1)) {
            double stopAcc = calculateAccelerationToStopAtPosition(closestStop - fPosition);
            int distAcc = (round(closestStop* 3.6)) -fSpeed;
            if (stopAcc < acceleration){
                acceleration = stopAcc;
                if (distAcc <= getKMinVersnelling())acceleration = distAcc;
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
    //unsigned int prevSpeed = fSpeed;
    if (lowerEnd < fSpeed + acceleration)fSpeed = lowerEnd;
    else fSpeed += (int) round(acceleration);
    if (fSpeed > 300) fSpeed =0;


    if (fPosition < 250 and kLicencePlate == std::string("koffiepot")and fCurrentRoad->getName() == std::string("E19")){
        std::cout << fSpeed << " " << acceleration << " " << fPosition <<"\n";
    }


//
//    if (acceleration < 0 and fSpeed > 300) {
//
//
//    } else if (acceleration > 0) {
//        if (fCurrentRoad->
//                getSpeedLimit(fPosition)
//            <
//
//            getKMaxSpeed() and
//
//            fCurrentRoad->
//                    getSpeedLimit(fPosition)
//            < fSpeed)
//            fSpeed = fCurrentRoad->getSpeedLimit(fPosition);
//        else if (fCurrentRoad->
//                getSpeedLimit(fPosition)
//                 >
//
//                 getKMaxSpeed() and
//
//                 getKMaxSpeed()
//
//                 > fSpeed)
//            fSpeed = getKMaxSpeed();
//    }
//
//    if (std::string("1THK180") == this->
//
//            getKLicencePlate()
//
//            ) {
//        std::cout << fSpeed << " " <<
//
//                  getKMaxSpeed()
//
//                  << " " <<
//                  std::endl;
//    }
//    if (std::string("651BUF") == this->
//
//            getKLicencePlate()
//
//            ) {
//        std::cout << fSpeed << " " <<
//
//                  getKMaxSpeed()
//
//                  << " " <<
//
//                  getKTypeName()
//
//                  <<
//                  std::endl;
//    }
//
//    if (prevSpeed == fSpeed)
//        this->
//
//                incAccelerationTimer();
//
//    else
//        this->
//
//                resetAccelerationTimer();
//
//    if (
//            fSpeed < fCurrentRoad->getSpeedLimit(fPosition) and fSpeed < this->getKMaxSpeed() and
//            getFNoAcceleration() >= 5
//            and round(fStroke) == fStroke and
//            (std::string("motorfiets") == this->getKTypeName() or this->getKTypeName() == std::string("auto")) and
//            fCurrentRoad->getFStrokes() > fStroke
//            ) {
//        fStroke += 0.2;
//        fGoingUp = true;
//    } else if (
//
//            getFNoAcceleration()
//
//            >= 5
//            and
//            round(fStroke)
//            ==
//            fStroke and
//            (std::string("motorfiets")
//             == this->
//
//                    getKTypeName()
//
//             or this->
//
//                    getKTypeName()
//
//                == std::string("auto")) and
//            fStroke > 1) {
//        fStroke -= 0.2;
//        fGoingUp = false;
//    } else if (fStroke !=
//               round(fStroke)
//            ) {
//        if (fGoingUp)fStroke += 0.2;
//        else fStroke -= 0.2;
//        if (fStroke -
//            floor(fStroke)
//            > 0.9)
//            fStroke = ceil(fStroke);
//        if (fStroke -
//            floor(fStroke)
//            < 0.1)
//            fStroke = floor(fStroke);
//    }
//



//if((unsigned int)getKMaxSpeed() < fSpeed) fSpeed = (unsigned int)getKMaxSpeed();//todo afremmen ?
}

void Vehicle::leaveRoad() {
    REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    fCurrentRoad = NULL;
    ENSURE(getFCurrentRoad() == NULL, "voertuig heeft baan niet verlaten");
}

double Vehicle::getCurrentStroke() {
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
    fNoAcceleration = 0;
}

void Vehicle::incAccelerationTimer() {
    fNoAcceleration++;
}

int Vehicle::getDistanceToNextVehicle(Vehicle *x, bool start) {
    if (fCurrentRoad ==NULL) return -1;
    if ((ceil(fStroke) == ceil(x->getCurrentStroke()) or ceil(fStroke) == floor(x->getCurrentStroke()) or
         floor(fStroke) == floor(x->getCurrentStroke()) or
         floor(fStroke) == ceil(x->getCurrentStroke())) and this != x) {
        int distance = (fPosition - x->getFPosition()) - getKLength();
        Road *startingRoad = x->getFCurrentRoad();
        while (startingRoad != fCurrentRoad and startingRoad != NULL) {
            distance += startingRoad->getLength();
            if (!startingRoad->getConnections().empty()){
                startingRoad = startingRoad->getConnections()[0];
            }
        }
        return distance;
    }

    if (fPrevVehicle == NULL)return -1;
    return fPrevVehicle->getDistanceToNextVehicle(x, false);
}

Vehicle *Vehicle::getFNextVehicle() const {
    return fNextVehicle;
}

void Vehicle::setFNextVehicle(Vehicle *NextVehicle) {
    Vehicle::fNextVehicle = NextVehicle;
}

void Vehicle::setFPrevVehicle(Vehicle *PrevVehicle) {
    Vehicle::fPrevVehicle = PrevVehicle;
}

bool Vehicle::operator<(const Vehicle &rhs) const {
    if (*rhs.getFCurrentRoad() == *fCurrentRoad and fPosition < rhs.getFPosition()) return true;
    return *fCurrentRoad > *rhs.getFCurrentRoad();
}

bool Vehicle::operator>(const Vehicle &rhs) const {
    if (*rhs.getFCurrentRoad() == *fCurrentRoad and fPosition > rhs.getFPosition()) return true;
    return *fCurrentRoad < *rhs.getFCurrentRoad();
}

bool Vehicle::operator<=(const Vehicle &rhs) const {
    return !(rhs < *this);
}

bool Vehicle::operator>=(const Vehicle &rhs) const {
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

bool Vehicle::isFGoingUp() const {
    return fGoingUp;
}

void Vehicle::setFGoingUp(bool GoingUp) {
    Vehicle::fGoingUp = GoingUp;
}

Bus::Bus(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad) : Vehicle(
        fSpeed, fPosition, kLicencePlate, fCurrentRoad), fTimeLeft(0) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

    fDistanceToNextStop = fCurrentRoad->getNextBusStop(fPosition) - fPosition;


}

const int Bus::getKLength() {
    return kLength;
}

const unsigned int Bus::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Bus::getKTypeName() {
    return "bus";
}

const int Bus::getKMinVersnelling() {
    return kMinVersnelling;
}

const int Bus::getKMaxVersnelling() {
    return kMaxVersnelling;
}

int Bus::getFDistanceToNextStop() const {
    return fDistanceToNextStop;
}

int Bus::getTimeLeft() const {
    return fTimeLeft;
}


void Bus::incTimeLeft() {
    Bus::fTimeLeft++;
    if (fTimeLeft == 31) {
        fTimeLeft = 0;
    }
}

void Bus::updateNextStop() {
    fDistanceToNextStop = getFCurrentRoad()->getNextBusStop(getFPosition()) - getFPosition();
}

Truck::Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad)
        : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

}

const int Truck::getKLength() {
    return kLength;
}

const unsigned int Truck::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Truck::getKTypeName() {
    return "vrachtwagen";
}

const int Truck::getKMinVersnelling() {
    return kMinVersnelling;
}

const int Truck::getKMaxVersnelling() {
    return kMaxVersnelling;
}

Motorcycle::Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate,
                       Road *fCurrentRoad) : Vehicle(fSpeed, fPosition, kLicencePlate, fCurrentRoad) {
    REQUIRE(fSpeed <= getKMaxSpeed(), "dit voertuig mag niet zo snel rijden");

}

const int Motorcycle::getKLength() {
    return kLength;
}

const unsigned int Motorcycle::getKMaxSpeed() {
    return kMaxSpeed;
}

const char *Motorcycle::getKTypeName() {
    return "motorfiets";
}

const int Motorcycle::getKMinVersnelling() {
    return kMinVersnelling;
}

const int Motorcycle::getKMaxVersnelling() {
    return kMaxVersnelling;
}
