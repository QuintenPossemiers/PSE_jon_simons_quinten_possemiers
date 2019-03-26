#include "Exeptions/AllExceptions.h"
#include "Vehicle.h"
#include <stdexcept>
#include <iostream>
#include <math.h>

bool Vehicle::operator==(const Vehicle &rhs) const {
    return license_plate == rhs.license_plate;
}

bool Vehicle::operator!=(const Vehicle &rhs) const {
    return !(rhs == *this);
}

bool Vehicle::collides(Vehicle *second_car) {
    return collides(second_car->getPosition(), second_car->getCurrent_road()->getName());
}

bool Vehicle::collides(double position, std::string road_name) {
    return road_name == current_road->getName() and this->position - 5 < position and position < this->position + 5;
}

unsigned int Vehicle::getSpeed() const {
    return speed;
}

void Vehicle::setSpeed(unsigned int speed) {
    Vehicle::speed = speed;
}

double Vehicle::getPosition() const {
    return position;
}

void Vehicle::setPosition(double position) {
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

Vehicle::Vehicle(unsigned int speed, double position, const std::string &license_plate,
                 Road *current_road, VehicleType* type) : speed(speed),
                                                                            position(position),
                                                                            license_plate(license_plate),
                                                                            current_road(current_road), type(type){

    if (current_road->getLength() < position) throw ParsingExc(vehicle_illegal_position);
    if (current_road->getSpeed_limit() < speed) throw ParsingExc(vehicle_speed_error);
}

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
    os << "Voertuig: " << vehicle.type->getName() << " (" + vehicle.license_plate << ")" << std::endl;
    os << " --> baan    : " << vehicle.current_road->getName() << std::endl;
    os << " --> positie : " << vehicle.position << std::endl;
    os << " --> snelheid: " << vehicle.speed << std::endl;
    return os;
}

bool Vehicle::set_new_position(unsigned int time_spent) {
    position += (speed / 3.6) * time_spent;
    if (position > current_road->getLength()) {
        position = 0;//je moet rekening houden met de overgang naar een andere baan
        if (current_road->getConnections().empty()) return false;
        this->setCurrent_road(current_road->getConnections()[0]);
        return true;
    }
    return true;
}

void Vehicle::set_new_speed(double acceleration) {
    speed += std::ceil(acceleration);//todo check ceil or round
    if (speed > 150)speed = 150;
    if (current_road->getSpeed_limit() < speed)speed = current_road->getSpeed_limit();
}

double Vehicle::get_acceleration(std::vector<Vehicle *> vehicles) {
    Vehicle *previous_veh = NULL;
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        if (this != vehicles[i] and previous_veh) {
            if ( vehicles[i]->position > position and previous_veh->position >  vehicles[i]->position) previous_veh =  vehicles[i];
        } else if (this !=  vehicles[i] and  vehicles[i]->position > position) {
            previous_veh =  vehicles[i];
        }
    }

    if (!previous_veh) return 2;

    double delta_ideal = 0.75 * this->speed + previous_veh->getLength() + 2;
    double delta_real = previous_veh->position - previous_veh->getLength() - position;
    double acceleration = 0.5 * (delta_real - delta_ideal);
    if (-8 >= acceleration)return -8;
    if (acceleration >= 2) return 2;
    return acceleration;
}


double Vehicle::getLength() const {
    return type->getLength();
}

Vehicle::~Vehicle() {

}



int VehicleType::getLength() const {
    return length;
}

VehicleType::VehicleType(const std::string &name) : name(name){
    if (name == "AUTO")length = 2;
}

std::string VehicleType::getName() {
    return name;
}
