//
// Created by Quinten on 3/9/2019.
//

#include "Road.h"
#include <stdexcept>

Road::Road(const std::string &name, unsigned int speed_limit, unsigned int length) :
        name(name),
        speed_limit(speed_limit),
        length(length) {
    if (name.length() == 0 or length == 0 or speed_limit == 0) throw std::invalid_argument("");
    //todo check this throw!
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
