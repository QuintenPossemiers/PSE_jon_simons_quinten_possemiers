
#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H


#include <string>
#include <vector>
#include <ostream>
#include "DesignByContract.h"

class Road {
private:
    std::string fName;
    unsigned int fSpeedLimit;
    unsigned int fLength;
    std::vector<Road *> fConnections;
    Road *_initCheck;

public:
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
    //ENSURE(fConnections.size()=i);

};


#endif //UNTITLED_ROAD_H
