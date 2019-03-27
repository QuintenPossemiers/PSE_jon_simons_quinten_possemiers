

#ifndef UNTITLED_SIMULATIONMODEL_H
#define UNTITLED_SIMULATIONMODEL_H

#include <string>
#include <ostream>
#include "Parser.h"


class SimulationModel {

private:

    SimulationModel* _initCheck;

    std::vector<Road *> fRoads;

    std::vector<Vehicle *> fVehicles;

public:
    SimulationModel();

    const std::vector<Vehicle *> &getVehicles() const;

    const std::vector<Road *> &getRoads() const;

public:
    void addRoad(Road *road);

    bool properlyInitialized();

    void addVehicle(Vehicle *vehicle);

    Road *doesRoadExist(std::string name);

    void start(const char *xml_path);

    void tick(unsigned int time = 1);

    void checkCollision(Vehicle* vehicle);

    void addConnection(Road* from, Road* to);

    void automaticSimulation();

    friend std::ostream &operator<<(std::ostream &os, const SimulationModel &model);

private:
    std::vector<Vehicle*> get_vehicle_on_road(Road* road);




};

#endif //UNTITLED_SIMULATIONMODEL_H
