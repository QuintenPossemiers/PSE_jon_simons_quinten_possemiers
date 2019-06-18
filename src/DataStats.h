//
// Created by quinten on 17.06.19.
//

#ifndef UNTITLED_DATASTATS_H
#define UNTITLED_DATASTATS_H

#include <iostream>
#include "DesignByContract.h"


class DataStats {
private:
    const std::string kLicencePlate;
    unsigned int fMaxSpeed;
    double fMeanSpeed;
    unsigned int fMovingTicks;
    unsigned int fTicks;
    DataStats *_initCheck;
public:
    DataStats(const std::string &fLicencePlate);
    //ENSURE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    bool properlyInitialised() const;

    DataStats();
    //ENSURE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    void toFile(const DataStats &stats);
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    const std::string &getKLicencePlate() const;
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    unsigned int getFMaxSpeed() const;
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    double getFMeanSpeed() const;
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    unsigned int getFMovingTicks() const;
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    unsigned int getFTicks() const;
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    void add(const unsigned int& rhs);
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");

    friend std::ostream &operator<<(std::ostream &os, const DataStats &stats);
    //REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");


};


#endif //UNTITLED_DATASTATS_H
