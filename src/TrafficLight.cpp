//
// Created by student on 30.04.19.
//

#include "TrafficLight.h"

void TrafficLight::clockCycle() {
    if (fCycle++ == 65) fCycle = 1;
    switch (fCycle) {
        case 31:
            fColor = "green";
            break;
        case 61:
            fColor = "orange";
            break;
        case 1:
            fColor = "red";
    }

}

std::string TrafficLight::getColor() {
    return fColor;
}

TrafficLight::TrafficLight(unsigned int position) : fCycle(1), fColor("red"),  fPosition(position), _initCheck(this){

}

bool TrafficLight::operator<(const TrafficLight &rhs) const {
    return fPosition < rhs.fPosition;
}

bool TrafficLight::operator>(const TrafficLight &rhs) const {
    return rhs < *this;
}

bool TrafficLight::operator<=(const TrafficLight &rhs) const {
    return !(rhs < *this);
}

bool TrafficLight::operator>=(const TrafficLight &rhs) const {
    return !(*this < rhs);
}

bool TrafficLight::operator==(const TrafficLight &rhs) const {
    return fPosition == rhs.fPosition;
}

bool TrafficLight::operator!=(const TrafficLight &rhs) const {
    return !(rhs == *this);
}

bool TrafficLight::properlyInitialised() {
    return this == _initCheck;
}
