
#include "Road.h"
#include <stdexcept>
#include "Exceptions.h"


Road::Road(const std::string &name, unsigned int speedLimit, unsigned int length, unsigned int strokes) :
        fName(name),
        fSpeedLimit(speedLimit),
        fLength(length),
        fStrokes(strokes),
        _initCheck(this) {
    if (length == 0)throw NonFatalException(road_length_null);
    if (speedLimit == 0)throw NonFatalException(road_speed_limit_null);
    ENSURE(properlyInitialized(), "baan niet goed geinitializeerd");
}


const std::string &Road::getName() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fName;
}

unsigned int Road::getSpeedLimit(unsigned int position) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(position <= this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    if (zones.empty() or zones.begin()->first > position)return fSpeedLimit;

    else {
        for (std::set<std::pair<unsigned int, unsigned int> >::iterator it = zones.begin(); it != zones.end();) {
            if (it->first > position) return (--it)->second;
            else if (it->first == position)return it->second;
            if (++it == zones.end()) return (--it)->second;
        }
    }
    return zones.end()->second;//cannot be reached
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

    if (road == this) throw NonFatalException(road_self_connection);
    fConnections.push_back(road);
}

bool Road::properlyInitialized() const {
    return _initCheck == this;
}

void Road::addBusStop(unsigned int position) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    fBusStops.insert(position);
    ENSURE(fBusStops.count(position) == 1, "bushalte kan niet worden toegevoegd");
}

int Road::getNextBusStop(unsigned int currentPosition) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(currentPosition <= this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");


    for (std::set<unsigned int>::iterator it = fBusStops.begin(); it != fBusStops.end(); ++it) {
        if (currentPosition <= *it)return *it - currentPosition;
    }
    for (unsigned int i = 0; i < fConnections.size(); ++i) {
        return fConnections[i]->getNextBusStop(0);
    }
    return -1;


}

void Road::addZone(unsigned int position, unsigned int speedLimit) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");

    zones.insert(std::make_pair(position, speedLimit));
    ENSURE(zones.count(std::make_pair(position, speedLimit)) == 1, "zone kan niet worden toegevoegd");
}

void Road::addTrafficLight(unsigned int position) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    fTrafficLights.insert(TrafficLight(position));
}

bool Road::operator<(const Road &rhs) const {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    if (&rhs == this) return true;
    if (fConnections.empty())return false;
    return *fConnections[0] < rhs;
}

bool Road::operator>(const Road &rhs) const {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    if (&rhs == this) return false;
    if (fConnections.empty())return true;
    return *fConnections[0] > rhs;
}

bool Road::operator<=(const Road &rhs) const {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return !(rhs < *this);
}

bool Road::operator>=(const Road &rhs) const {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return !(*this < rhs);
}

unsigned int Road::getFStrokes() const {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    return fStrokes;
}

unsigned int Road::getIsNextTrafficStop(unsigned int currentPosition) {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    REQUIRE(currentPosition <= this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");


    for (std::set<TrafficLight>::iterator it = fTrafficLights.begin(); it != fTrafficLights.end(); ++it) {
        if (it->getFPosition() >= currentPosition and it->getFColor() != "green") {
            return it->getFPosition() - currentPosition;
        }
    }
    return -1;

}

void Road::tickVerkeersLichten() {
    REQUIRE(properlyInitialized(), "baan is niet geinitialiseerd");
    std::set<TrafficLight> y;
    std::set<TrafficLight>::iterator it;
    for (it = fTrafficLights.begin(); it != fTrafficLights.end(); ++it) {
        TrafficLight x = *it;
        x.clockCycle();
        y.insert(x);
    }
    fTrafficLights = y;

}


