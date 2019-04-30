
#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H


#include <string>
#include <vector>
#include <set>
#include <ostream>
#include "DesignByContract.h"

class Road {
private:
    std::string fName;
    unsigned int fSpeedLimit;
    unsigned int fLength;
    std::vector<Road *> fConnections;
    std::set<unsigned int> fBusStops;

    Road *_initCheck;

public:
    void addBusStop(unsigned int position);
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");
    //REQUIRE(position < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    //ENSURE(fBusStops.count(position)==1,"bushalte kan niet worden toegevoegd")

    int getNextBusStop(unsigned int currentPosition);
    //REQUIRE(currentPosition < this->getLength(), "positie moet kleiner zijn dan de lengte van de baan");
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");


    const std::string &getName();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    unsigned int getSpeedLimit();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    unsigned int getLength();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    const std::vector<Road *> &getConnections();
    //REQUIRE(properlyInitialized(),"baan is niet geinitialiseerd");

    bool properlyInitialized();

    Road(const std::string &name, unsigned int speedLimit, unsigned int length);
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
};


#endif //UNTITLED_ROAD_H
