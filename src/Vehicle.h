#ifndef UNTITLED_VEHICLE_H
#define UNTITLED_VEHICLE_H

#include <string>
#include <vector>
#include <ostream>
#include "Road.h"
#include <set>
#include "DesignByContract.h"

class VehicleType {
private:
    int fLength;
    std::string fName;
public:
    explicit VehicleType(const std::string &name);

    int getLength() const;

    std::string getName();
};

class Vehicle {
private:
    unsigned int fSpeed;
    unsigned int fPosition;
    const std::string kLicencePlate;
    Road *fCurrentRoad;
    VehicleType *fType;
    Vehicle *_initCheck;


public:
    unsigned int getLength();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd")
    //REQUIRE(fType != NULL,"voertuig heeft geen geldig type")

    unsigned int getSpeed();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd")

    void setSpeed(unsigned int speed);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //mss is een max speed ook wel leuk
    //ENSURE(speed == fSpeed, "snelheid niet aangepast");

    unsigned int getPosition();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    void setPosition(unsigned int position);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(position == fPosition,"positie niet aangepast");

    Road *getCurrentRoad();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");

    void setCurrentRoad(Road *currentRoad);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(currentRoad!= NULL,"baan moet bestaan");
    //ENSURE(fCurrentRoad == currentRoad, "baan niet aangepast");

    bool properlyInitialized();

    Vehicle(unsigned int speed, unsigned int position, const std::string &licenePlate,
            Road *currentRoad, VehicleType *type);
    //ENSURE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(currentRoad!= NULL,"baan moet bestaan");
    //REQUIRE(type!= NULL,"type moet bestaan");

    virtual ~Vehicle();

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


    bool setNewPosition(unsigned int timeSpent = 1);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");


    void setAcceleration(double acceleration);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //REQUIRE(acceleration > 2,"acceleration hoger dan 2");
    //REQUIRE(acceleration < -8, " acceleration lager dan -8");


    double getAcceleration(std::vector<Vehicle *> vehicles);
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(acceleration >= 2,"acceleration hoger dan 2");
    //ENSURE(acceleration <= -8, " acceleration lager dan -8");

    void leaveRoad();
    //REQUIRE(properlyInitialized(),"voertuig niet goed geinitializeerd");
    //ENSURE(fCurrentRoad ==NULL, "voertuig heeft baan niet verlaten");


};


#endif //UNTITLED_VEHICLE_H
