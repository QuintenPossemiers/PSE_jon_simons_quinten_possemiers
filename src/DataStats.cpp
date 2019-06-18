//
// Created by quinten on 17.06.19.
//

#include "DataStats.h"

DataStats::DataStats(const std::string &fLicencePlate) : kLicencePlate(fLicencePlate), fMaxSpeed(), fMeanSpeed(), fMovingTicks(), fTicks() {}

void DataStats::add(const unsigned int &rhs) {
    if (fMaxSpeed < rhs)fMaxSpeed = rhs;
    if (rhs != 0)fMovingTicks++;
    double totalSpeed = (fTicks++*fMeanSpeed) + rhs;
    fMeanSpeed = totalSpeed/fTicks;
}

std::ostream &operator<<(std::ostream &os, const DataStats &stats) {
    os << stats.fTicks << " " << stats.kLicencePlate<< " " << stats.fMaxSpeed<<" " << stats.fMovingTicks << std::endl;
    return os;
}

DataStats::DataStats() : fMaxSpeed(), fMeanSpeed(), fMovingTicks(), fTicks() {

}
