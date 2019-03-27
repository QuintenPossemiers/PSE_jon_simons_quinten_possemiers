
#include "Road.h"
#include <stdexcept>
#include "Exceptions.h"

Road::Road(const std::string &name, unsigned int speedLimit, unsigned int length) :
        fName(name),
        fSpeedLimit(speedLimit),
        fLength(length),
        _initCheck(this){
    if (length == 0)throw NonFatalException(road_length_null);
    if (speedLimit == 0)throw NonFatalException(road_speed_limit_null);
}

const std::string &Road::getName() const {
    return fName;
}

void Road::setName(const std::string &name) {
    Road::fName = name;
}

unsigned int Road::getSpeedLimit() const {
    return fSpeedLimit;
}

void Road::setSpeedLimit(unsigned int speed_limit) {
    Road::fSpeedLimit = speed_limit;
}

unsigned int Road::getLength() const {
    return fLength;
}

const std::vector<Road *> &Road::getConnections() const {
    return fConnections;
}

bool Road::operator==(const Road &rhs) const {
    return fName == rhs.fName;
}

bool Road::operator!=(const Road &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Road &road) {
    os << "Baan: " << road.fName << std::endl;
    os << " --> snelheidslimiet  : " << road.fSpeedLimit << std::endl;
    os << " --> lengte           : " << road.fLength << std::endl;
    for (unsigned int i = 0; i < road.getConnections().size(); ++i) {
        os << " --> verbinding       : " << road.getConnections()[i]->getName() << std::endl;
    }

    return os;
}

void Road::addConnection(Road *road) {
    if (road == this) throw NonFatalException(road_self_connection);
    fConnections.push_back(road);
}

bool Road::properlyInitialized() {
    return _initCheck == this;
}
