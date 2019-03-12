//
// Created by Quinten on 3/9/2019.
//

#include "Road.h"
#include <stdexcept>
#include "Exeptions/AllExceptions.h"

Road::Road(const std::string &name, unsigned int speed_limit, unsigned int length) :
        name(name),
        speed_limit(speed_limit),
        length(length) {
    if (length == 0)throw ParsingExc(ParsingErr::road_length_null);
    if (speed_limit == 0)throw ParsingExc(ParsingErr::road_speed_limit_null);
}

const std::string &Road::getName() const {
    return name;
}

void Road::setName(const std::string &name) {
    Road::name = name;
}

unsigned int Road::getSpeed_limit() const {
    return speed_limit;
}

void Road::setSpeed_limit(unsigned int speed_limit) {
    Road::speed_limit = speed_limit;
}

unsigned int Road::getLength() const {
    return length;
}

const std::vector<Road *> &Road::getConnections() const {
    return connections;
}

bool Road::operator==(const Road &rhs) const {
    return name == rhs.name;
}

bool Road::operator!=(const Road &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Road &road) {
    os << "Baan: " << road.name << std::endl;
    os << " --> snelheidslimiet  : " << road.speed_limit << std::endl;
    os << " --> lengte           : " << road.length << std::endl;
    return os;
}

void Road::add_connection(Road *road) {
    if (road == this) throw ParsingExc(ParsingErr::road_self_connection);
    connections.push_back(road);
}
