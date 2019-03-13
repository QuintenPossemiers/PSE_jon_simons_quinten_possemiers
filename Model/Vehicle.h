#ifndef UNTITLED_VEHICLE_H
#define UNTITLED_VEHICLE_H

#include <string>
#include <vector>
#include <ostream>
#include "Road.h"

class Vehicle {

    /**section reserved for variables*/
private:
    unsigned int speed;
    double position;
    std::string license_plate, type;
    Road *current_road;

    /**section for getters and setters*/
public:
    unsigned int getSpeed() const;

    void setSpeed(unsigned int speed);

    double getPosition() const;

    void setPosition(unsigned int position);

    const std::string &getLicense_plate() const;

    void setLicense_plate(const std::string &license_plate);

    Road *getCurrent_road() const;

    void setCurrent_road(Road *current_road);

    /**section reserved for constructor
     *
     * Position cannot be greater than the size of the road!
     * Speed cannot be greater than the speed limit of the the road!
     * */

    Vehicle(unsigned int speed, unsigned int position, const std::string &license_plate, const std::string &type,
            Road *current_road);

    /**section for overloading operators*/
public:
    friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle);

    bool operator==(const Vehicle &rhs) const;

    bool operator!=(const Vehicle &rhs) const;

    /**section for public functions*/
public:
    bool collides(Vehicle* second_car);

    bool collides(unsigned int position, std::string road_name);

    void set_new_position(unsigned int time_spent = 1); // time spent

};


#endif //UNTITLED_VEHICLE_H
