
#include "Road.h"
#include <stdexcept>
#include "Exceptions.h"

Road::Road(const std::string &name, unsigned int speedLimit, unsigned int length) :
        fName(name),
        fSpeedLimit(speedLimit),
        fLength(length),
        _initCheck(this) {
    if (length == 0)throw NonFatalException(road_length_null);
    if (speedLimit == 0)throw NonFatalException(road_speed_limit_null);
    ENSURE(properlyInitialized(), "baan niet goed geinitializeerd");
}

const std::string &Road::getName() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fName;
}

unsigned int Road::getSpeedLimit() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fSpeedLimit;
}


unsigned int Road::getLength() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fLength;
}

const std::vector<Road *> &Road::getConnections() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fConnections;
}

bool Road::operator==(Road &road) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fName == road.fName;
}

bool Road::operator!=(Road &road) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");

    return !(road == *this);
}

std::ostream &operator<<(std::ostream &os, Road &road) {
    REQUIRE(road.properlyInitialized(), "baan is niet geinitialiseerd");
    os << "Baan: " << road.fName << std::endl;
    os << " --> snelheidslimiet  : " << road.fSpeedLimit << std::endl;
    os << " --> lengte           : " << road.fLength << std::endl;
    for (unsigned int i = 0; i < road.getConnections().size(); ++i) {
        os << " --> verbinding       : " << road.getConnections()[i]->getName() << std::endl;
    }

    return os;
}

void Road::addConnection(Road *road) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(road != NULL, "geen geldige baan");

    unsigned int i = (unsigned int) fConnections.size() + 1;

    if (road == this) throw NonFatalException(road_self_connection);
    fConnections.push_back(road);
    ENSURE(fConnections.size() == i, "connectie niet toegevoegd");
}

bool Road::properlyInitialized() {
    return _initCheck == this;
}
