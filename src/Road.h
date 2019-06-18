
#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H


#include <string>
#include <vector>
#include <set>
#include <ostream>
#include "TrafficLight.h"
#include "DesignByContract.h"

class Road {
private:
    std::string fName;
    unsigned int fSpeedLimit;
    unsigned int fLength;
    std::vector<Road *> fConnections;
    std::set<unsigned int> fBusStops;
    std::set<std::pair<unsigned int, unsigned int> > zones;
    std::set<TrafficLight> fTrafficLights;
    unsigned int fStrokes;

    Road *_initCheck;


public:
    bool operator<(const Road &rhs) const;

    bool operator>(const Road &rhs) const;

    bool operator<=(const Road &rhs) const;

    bool operator>=(const Road &rhs) const;



public:

    unsigned int getFStrokes() const;

    void addBusStop(unsigned int position);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    //ENSURE(fBusStops.count(position)==1,"bushalte kan niet worden toegevoegd")

    void addTrafficLight(unsigned int position);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");



    void addZone(unsigned int position, unsigned int speedLimit);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(speedLimit < fSpeedLimit, "zone moet snelheidslimiet respecteren!")
    //REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    //ENSURE(zones.count(std::make_pair(position, speedLimit))==1,"zone kan niet worden toegevoegd");

    int getNextBusStop(unsigned int currentPosition);
    //REQUIRE(currentPosition < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");


    unsigned int getIsNextTrafficStop(unsigned int currentPosition);


    const std::string &getName();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    unsigned int getSpeedLimit(unsigned int position);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");


    unsigned int getLength();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    const std::vector<Road *> &getConnections();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    bool properlyInitialized();

    Road(const std::string &name, unsigned int speedLimit, unsigned int length, unsigned int strokes=2);
    //ENSURE(properlyInitialized(), "baan niet goed geinitializeerd");

    friend std::ostream &operator<<(std::ostream &os, Road &road);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    bool operator==(Road &road);
    /**
     * Works based on name
     */
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    bool operator!=(Road &road);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");


    void addConnection(Road *road);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(road != NULL, "geen geldige baan");

    void tickVerkeersLichten();
};


#endif //UNTITLED_ROAD_H
