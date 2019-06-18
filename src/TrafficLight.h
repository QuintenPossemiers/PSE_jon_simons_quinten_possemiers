#include <iostream>

#ifndef UNTITLED_TRAFFICLIGHT_H
#define UNTITLED_TRAFFICLIGHT_H


class TrafficLight {
private:
    int fCycle;
    std::string fColor;
    unsigned int fPosition;
    TrafficLight* _initCheck;
public:

    bool properlyInitialised();

    TrafficLight(unsigned int position);

    void clockCycle();

    std::string getColor();

    const std::string &getFColor() const;

    unsigned int getFPosition() const;

    bool operator<(const TrafficLight &rhs) const;

    bool operator>(const TrafficLight &rhs) const;

    bool operator<=(const TrafficLight &rhs) const;

    bool operator>=(const TrafficLight &rhs) const;

    bool operator==(const TrafficLight &rhs) const;

    bool operator!=(const TrafficLight &rhs) const;

};


#endif //UNTITLED_TRAFFICLIGHT_H
