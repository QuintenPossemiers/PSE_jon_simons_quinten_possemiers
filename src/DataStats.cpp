//
// Created by quinten on 17.06.19.
//

#include <fstream>
#include <sstream>
#include "DataStats.h"


DataStats::DataStats(const std::string &fLicencePlate) : kLicencePlate(fLicencePlate), fMaxSpeed(), fMeanSpeed(), fMovingTicks(), fTicks(), _initCheck(this){
    ENSURE(properlyInitialised(),"Datastats niet goed geinitializeerd");
}

void DataStats::add(const unsigned int &rhs) {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    if (fMaxSpeed < rhs)fMaxSpeed = rhs;
    if (rhs != 0)fMovingTicks++;
    double totalSpeed = (fTicks++*fMeanSpeed) + rhs;
    fMeanSpeed = totalSpeed/fTicks;
}

std::ostream &operator<<(std::ostream &os, const DataStats &stats) {
    REQUIRE(stats.properlyInitialised(),"Datastats niet goed geinitializeerd");
    os << "Aantal seconden: " << stats.getFTicks() << "\n";
    os<< "Nummerplaat: " + stats.getKLicencePlate() + "\n";
    os << "Maximale snelheid: " << stats.getFMaxSpeed() << "\n";
    os << "Gemiddelde snelheid: " << stats.getFMeanSpeed() << "\n";
    os << "Aantal seconden in beweging " << stats.getFMovingTicks()<< "\n";
    os << "Aantal seconden in stilstand " << stats.getFTicks()-stats.getFMovingTicks() <<"\n";
    os << "Afgelegde afstand " << stats.getFMeanSpeed()/(3.6)*stats.getFTicks() <<"\n";
    return os;
}
bool DataStats::properlyInitialised() const{
    return this == _initCheck;
}



DataStats::DataStats() : fMaxSpeed(), fMeanSpeed(), fMovingTicks(), fTicks() ,_initCheck(this){
    ENSURE(properlyInitialised(),"Datastats niet goed geinitializeerd");

}

const std::string &DataStats::getKLicencePlate() const {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    return kLicencePlate;
}

unsigned int DataStats::getFMaxSpeed() const {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    return fMaxSpeed;
}

double DataStats::getFMeanSpeed() const {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    return fMeanSpeed;
}

unsigned int DataStats::getFMovingTicks() const {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    return fMovingTicks;
}

unsigned int DataStats::getFTicks() const {
    REQUIRE(properlyInitialised(),"Datastats niet goed geinitializeerd");
    return fTicks;
}
