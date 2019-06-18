//
// Created by quinten on 17.06.19.
//

#ifndef UNTITLED_DATASTATS_H
#define UNTITLED_DATASTATS_H

#include <iostream>


class DataStats {
private:
    const std::string kLicencePlate;
    unsigned int fMaxSpeed;
    double fMeanSpeed;
    unsigned int fMovingTicks;
    unsigned int fTicks;
public:
    DataStats(const std::string &fLicencePlate);

    DataStats();

    void toFile(const DataStats &stats);

    const std::string &getKLicencePlate() const;

    unsigned int getFMaxSpeed() const;

    double getFMeanSpeed() const;

    unsigned int getFMovingTicks() const;

    unsigned int getFTicks() const;

    void add(const unsigned int& rhs);

    friend std::ostream &operator<<(std::ostream &os, const DataStats &stats);



};


#endif //UNTITLED_DATASTATS_H
