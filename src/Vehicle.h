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
    bool isFGoingUp() ;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    void setFGoingUp(bool fGoingUp);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(fGoingUp == isFGoingUp, "fGoingUp niet aangepast")

    void setFPrevVehicle(Vehicle *fPrevVehicle);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(fPrevVehicle == getFPrevVehicle, "fPrevVehicle niet aangepast")

private:

public:
    bool operator<(const Vehicle &rhs) const;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool operator>(const Vehicle &rhs) const;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool operator<=(const Vehicle &rhs) const;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    bool operator>=(const Vehicle &rhs) const;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

private:

    double calculateAccelerationToStopAtPosition(int distance);


public:
    Vehicle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);
    //REQUIRE(fCurrentRoad != NULL, "baan moet bestaan");
    //ENSURE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    bool properlyInitialised() const ;

    virtual const int getKLength() = 0;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const unsigned int getKMaxSpeed() = 0;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMaxVersnelling() = 0;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMinVersnelling() = 0;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const char* getKTypeName() = 0;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    unsigned int getFSpeed() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    Vehicle *getFNextVehicle() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    void setFNextVehicle(Vehicle *fNextVehicle);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(fNextVehicle== getFNextVehicle(), "nextvehicle niet aangepast");

    unsigned int getNextVehocleSize(double stroke);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    unsigned int getFNoAcceleration() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    unsigned int getFPosition() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    unsigned int getRadiusOnStroke(int stroke);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    const std::string &getKLicencePlate() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    int getDistanceToNextVehicle(Vehicle* x, bool start=true);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    Road *getFCurrentRoad() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    Vehicle *getFPrevVehicle() ;
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

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
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    void setFStroke(double fStroke);
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(getCurrentStroke() == fStroke, "strook niet aangepast");

    void resetAccelerationTimer();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(fNoAcceleration == 0; "fNoAcceleration is niet op 0 gezet");

    void incAccelerationTimer();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");


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
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const unsigned int getKMaxSpeed();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const char* getKTypeName();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMaxVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMinVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
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
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMinVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    int getFDistanceToNextStop() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    int getTimeLeft() const;
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    void updateNextStop();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    void incTimeLeft();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
    //ENSURE(fTimeLeft>=0,"time left kleiner dan 0");
    //ENSURE(fTimeLeft>31,"time left groter dan 31");

public:
    virtual const int getKLength();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const unsigned int getKMaxSpeed();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const char* getKTypeName();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
};

class Truck : public Vehicle {
public:
    Truck(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 15;

    static const unsigned int kMaxSpeed = 90;

    static const int kMinVersnelling =-6;

    static const int kMaxVersnelling =1;

    virtual const int getKMaxVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMinVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

public:
    virtual const int getKLength();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const unsigned int getKMaxSpeed();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const char* getKTypeName();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
};
class Motorcycle : public Vehicle {
public:
    Motorcycle(unsigned int fSpeed, unsigned int fPosition, const std::string &kLicencePlate, Road *fCurrentRoad);

    static const int kLength = 1;

    static const int kMaxSpeed = 180;

    static const int kMinVersnelling =-10;

    static const int kMaxVersnelling =4;

    virtual const int getKMaxVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const int getKMinVersnelling();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

public:
    virtual const int getKLength();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const unsigned int getKMaxSpeed();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");

    virtual const char* getKTypeName();
    //REQUIRE(properlyInitialised(), "voertuig niet goed geinitializeerd");
};







#endif //REWRITESYICK_VEHICLE_H
