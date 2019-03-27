#ifndef UNTITLED_VEHICLE_H
#define UNTITLED_VEHICLE_H

#include <string>
#include <vector>
#include <ostream>
#include "Road.h"
#include <set>

class VehicleType{
private:
    int fLength;
    std::string fName;
public:
    explicit VehicleType(const std::string &name);

    int getLength() const;

    std::string getName();
};

class Vehicle {
    /**section reserved for variables*/
private:
    unsigned int fSpeed;
    unsigned int fPosition;
    const std::string kLicencePlate;
    Road *fCurrentRoad;
    VehicleType* fType;
    Vehicle* _initCheck;



    /**section for getters and setters*/
public:
    unsigned int getLength() const;

    unsigned int getSpeed() const;

    void setSpeed(unsigned int speed);

    unsigned int getPosition() const;

    void setPosition(unsigned int position);

    const std::string &getLicencePlate() const;

    Road *getCurrentRoad() const;

    void setCurrentRoad(Road *currentRoad);

    bool properlyInitialized();

    /**section reserved for constructor
     *
     * Position cannot be greater than the size of the road!
     * Speed cannot be greater than the speed limit of the the road!
     * */

    Vehicle(unsigned int speed, unsigned int position, const std::string &licenePlate,
            Road *currentRoad, VehicleType* type);

    virtual ~Vehicle();

    /**section for overloading operators*/
public:
    friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle);

    bool operator==(const Vehicle &rhs) const;

    bool operator!=(const Vehicle &rhs) const;

    /**section for public functions*/
public:
    bool collides(Vehicle* secondCar);

    bool collides(double position, std::string roadName);

    bool setNewPosition(unsigned int timeSpent = 1); // time spent

    void setAcceleration(double acceleration);

    double getAcceleration(std::vector<Vehicle *> vehicles);
};


#endif //UNTITLED_VEHICLE_H
