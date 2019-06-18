#ifndef REWRITESYICK_VEHICLE_H
#define REWRITESYICK_VEHICLE_H

#include <iostream>
#include "Road.h"
#include "Exceptions.h"

class Vehicle {
private:
    unsigned int fSpeed;

    unsigned int fNoAcceleration;

    unsigned int fPosition;

    bool fGoingUp;

    const std::string kLicencePlate;

    Road *fCurrentRoad;

    Vehicle *fPrevVehicle;

    Vehicle *fNextVehicle;

    double fStroke;

    Vehicle *_initCheck;
public:
    bool isFGoingUp() const;

    void setFGoingUp(bool fGoingUp);

    void setFPrevVehicle(Vehicle *fPrevVehicle);

private:

public:
    bool operator<(const Vehicle &rhs) const;

    bool operator>(const Vehicle &rhs) const;

    bool operator<=(const Vehicle &rhs) const;

    bool operator>=(const Vehicle &rhs) const;

private:

    double calculateAccelerationToStopAtPosition(int distance);


public:
    Vehicle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    bool properlyInitialised();

    virtual const int getKLength() = 0;

    virtual const unsigned int getKMaxSpeed() = 0;

    virtual const int getKMaxVersnelling() = 0;

    virtual const int getKMinVersnelling() = 0;

    virtual const char* getKTypeName() = 0;

    unsigned int getFSpeed() const;

    Vehicle *getFNextVehicle() const;

    void setFNextVehicle(Vehicle *fNextVehicle);

    unsigned int getNextVehocleSize(double stroke);

    unsigned int getFNoAcceleration() const;

    unsigned int getFPosition() const;

    unsigned int getRadiusOnStroke(int stroke);

    const std::string &getKLicencePlate() const;

    int getDistanceToNextVehicle(Vehicle* x, bool start=true);

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

    bool collides(double position, std::string roadName, double stroke);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool updatePosition();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    void updateSpeed();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(acceleration > getMaxVersnelling(),"acceleration hoger dan max versnelling");
    //ENSURE(acceleration < getMinVersnelling(), " acceleration lager dan min versnelling");

    void leaveRoad();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(getFCurrentRoad() ==NULL, "voertuig heeft baan niet verlaten");

    double getCurrentStroke();

    void setFStroke(double fStroke);

    void resetAccelerationTimer();

    void incAccelerationTimer();


};

class Car : public Vehicle {
public:
    Car(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 3;

    static const unsigned int kMaxSpeed = 150;

    static const int kMinVersnelling =-8;

    static const int kMaxVersnelling =2;


public:
    virtual const int getKLength();

    virtual const unsigned int getKMaxSpeed();

    virtual const char* getKTypeName();

    virtual const int getKMaxVersnelling();

    virtual const int getKMinVersnelling();
};

class Bus : public Vehicle {
private:
    int fDistanceToNextStop;

    int fTimeLeft;
public:
    Bus(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 10;

    static const unsigned int kMaxSpeed = 70;

    static const int kMinVersnelling =-7;

    static const int kMaxVersnelling =1;

    virtual const int getKMaxVersnelling();

    virtual const int getKMinVersnelling();

    int getFDistanceToNextStop() const;

    int getTimeLeft() const;

    void updateNextStop();

    void incTimeLeft();

public:
    virtual const int getKLength();

    virtual const unsigned int getKMaxSpeed();

    virtual const char* getKTypeName();
};

class Truck : public Vehicle {
public:
    Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 15;

    static const unsigned int kMaxSpeed = 90;

    static const int kMinVersnelling =-6;

    static const int kMaxVersnelling =1;

    virtual const int getKMaxVersnelling();

    virtual const int getKMinVersnelling();

public:
    virtual const int getKLength();

    virtual const unsigned int getKMaxSpeed();

    virtual const char* getKTypeName();
};
class Motorcycle : public Vehicle {
public:
    Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 1;

    static const int kMaxSpeed = 180;

    static const int kMinVersnelling =-10;

    static const int kMaxVersnelling =4;

    virtual const int getKMaxVersnelling();

    virtual const int getKMinVersnelling();

public:
    virtual const int getKLength();

    virtual const unsigned int getKMaxSpeed();

    virtual const char* getKTypeName();
};







#endif //REWRITESYICK_VEHICLE_H
