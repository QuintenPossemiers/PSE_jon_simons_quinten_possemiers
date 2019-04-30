#ifndef REWRITESYICK_VEHICLE_H
#define REWRITESYICK_VEHICLE_H

#include <iostream>
#include "Road.h"
#include "Exceptions.h"

class Vehicle {
private:
    unsigned int fSpeed;

    unsigned int fPosition;

    const std::string kLicencePlate;

    Road *fCurrentRoad;

    Vehicle *fPrevVehicle;

    Vehicle *_initCheck;

public:
    Vehicle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    bool properlyInitialised();

    virtual const int getKLength() = 0;

    virtual const int getKMaxSpeed() = 0;

    virtual const char* getKTypeName() = 0;

    unsigned int getFSpeed() const;

    unsigned int getFPosition() const;

    const std::string &getKLicencePlate() const;

    Road *getFCurrentRoad() const;

    Vehicle *getFPrevVehicle() const;

    void setSpeed(unsigned int speed);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //mss is een max speed ook wel leuk
    //ENSURE(speed == getFSpeed(), "snelheid niet aangepast");

    void setPosition(unsigned int position);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(position == getFPosition(),"positie niet aangepast");

    void setCurrentRoad(Road *currentRoad);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(currentRoad!= NULL,"baan moet bestaan");
    //ENSURE(getFCurrentRoad() == currentRoad, "baan niet aangepast");

    friend std::ostream &operator<<(std::ostream &os, Vehicle &vehicle);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(vehicle!=NULL,"voertuig moet bestaan");

    bool operator==(Vehicle &rhs);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool operator!=(Vehicle &rhs);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool collides(Vehicle *secondCar);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(secondCar!=NULL,"voertuig moet bestaan");

    bool collides(double position, std::string roadName);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool setNewPosition();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    void updateSpeed();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(acceleration > 2,"acceleration hoger dan 2");
    //REQUIRE(acceleration < -8, " acceleration lager dan -8");

    void leaveRoad();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(getFCurrentRoad() ==NULL, "voertuig heeft baan niet verlaten");


};

class Car : public Vehicle {
public:
    Car(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 3;

    static const int kMaxSpeed = 150;

public:
    virtual const int getKLength();

    virtual const int getKMaxSpeed();

    virtual const char* getKTypeName();
};

class Bus : public Vehicle {
public:
    Bus(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 10;

    static const int kMaxSpeed = 70;

public:
    virtual const int getKLength();

    virtual const int getKMaxSpeed();

    virtual const char* getKTypeName();
};

class Truck : public Vehicle {
public:
    Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 15;

    static const int kMaxSpeed = 90;

public:
    virtual const int getKLength();

    virtual const int getKMaxSpeed();

    virtual const char* getKTypeName();
};
class Motorcycle : public Vehicle {
public:
    Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 1;

    static const int kMaxSpeed = 180;

public:
    virtual const int getKLength();

    virtual const int getKMaxSpeed();

    virtual const char* getKTypeName();
};







#endif //REWRITESYICK_VEHICLE_H
