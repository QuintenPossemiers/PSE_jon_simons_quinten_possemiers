
#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H


#include <string>
#include <vector>
#include <ostream>

class Road {
private:
    std::string fName;
    unsigned int fSpeedLimit;
    unsigned int fLength;
    std::vector<Road *> fConnections;
    Road* _initCheck;

public:
    const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getSpeedLimit() const;

    void setSpeedLimit(unsigned int speed_limit);

    unsigned int getLength() const;

    const std::vector<Road *> &getConnections() const;

    bool properlyInitialized();

    Road(const std::string &name, unsigned int speedLimit, unsigned int length);

    friend std::ostream &operator<<(std::ostream &os, const Road &road);

    bool operator==(const Road &rhs) const;

    bool operator!=(const Road &rhs) const;

    void addConnection(Road *road);
};


#endif //UNTITLED_ROAD_H
