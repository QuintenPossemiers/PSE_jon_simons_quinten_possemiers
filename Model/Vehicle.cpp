//
// Created by Quinten on 3/9/2019.
//

#include "Vehicle.h"
#include <stdexcept>
#include <iostream>

bool Vehicle::operator==(const Vehicle &rhs) const {
    return license_plate == rhs.license_plate;
}

bool Vehicle::operator!=(const Vehicle &rhs) const {
    return !(rhs == *this);
}

bool Vehicle::collides(Vehicle *second_car) {
    return collides(second_car->getPosition(), second_car->getCurrent_road()->getName());
}

bool Vehicle::collides(unsigned int position, std::string road_name) {
    return road_name == current_road->getName() and this->position - 5 < position and position < this->position + 5;
}

unsigned int Vehicle::getSpeed() const {
    return speed;
}

void Vehicle::setSpeed(unsigned int speed) {
    Vehicle::speed = speed;
}

unsigned int Vehicle::getPosition() const {
    return position;
}

void Vehicle::setPosition(unsigned int position) {
    Vehicle::position = position;
}

const std::string &Vehicle::getLicense_plate() const {
    return license_plate;
}

void Vehicle::setLicense_plate(const std::string &license_plate) {
    Vehicle::license_plate = license_plate;
}

Road *Vehicle::getCurrent_road() const {
    return current_road;
}

void Vehicle::setCurrent_road(Road *current_road) {
    Vehicle::current_road = current_road;
}

Vehicle::Vehicle(unsigned int speed, unsigned int position, const std::string &license_plate,
                 const std::string &type, Road *current_road) : speed(speed),
                                                                position(position),
                                                                license_plate(license_plate),
                                                                type(type),
                                                                current_road(current_road) {
if (current_road->getLength() < position or current_road->getSpeed_limit()<speed)
    throw std::invalid_argument("");
    //todo check this throw!

}


