#include "Vehicle.h"
#include "Exceptions.h"

bool test(Vehicle *number) {
    return number->getCurrentRoad() == NULL;
};

#include <iostream>
#include <algorithm>
#include "SimulationModel.h"

SimulationModel::SimulationModel() : _initCheck(this) {

};

void SimulationModel::addRoad(Road *road) {
    if (doesRoadExist(road->getName()) != NULL)
        throw NonFatalException(road_dupe_name);
    fRoads.push_back(road);
}

void SimulationModel::addVehicle(Vehicle *vehicle) {

    if (NULL == doesRoadExist(vehicle->getCurrentRoad()->getName()))
        throw FatalException(non_existing_road);
    checkCollision(vehicle);

    fVehicles.push_back(vehicle);
}


Road *SimulationModel::doesRoadExist(std::string name) {
    for (unsigned int i = 0; i < fRoads.size(); ++i) {
        if (fRoads[i]->getName() == name) return fRoads[i];
    }
    return NULL;
}

const std::vector<Vehicle *> &SimulationModel::getVehicles() const {
    return fVehicles;
}

void SimulationModel::start(const char *xml_path) {
    fVehicles.clear();
    fRoads.clear();
    Parser parser = Parser(xml_path);
    parser.initialiseRoadsAndVehicles(this);
}

std::ostream &operator<<(std::ostream &os, const SimulationModel &model) {

    for (unsigned int i = 0; i < model.getRoads().size(); ++i) {
        os << *model.getRoads()[i] << std::endl;
    }

    for (unsigned int j = 0; j < model.getVehicles().size(); ++j) {
        os << *model.getVehicles()[j] << std::endl;
    }
    return os;
}

const std::vector<Road *> &SimulationModel::getRoads() const {
    return fRoads;
}

std::vector<Vehicle *> SimulationModel::get_vehicle_on_road(Road *road) {
    std::vector<Vehicle *> vehiclesOnRoad;

    for (unsigned int i = 0; i < fVehicles.size(); ++i)
        if (fVehicles[i]->getCurrentRoad() == road)vehiclesOnRoad.push_back(fVehicles[i]);


    return vehiclesOnRoad;
}

void SimulationModel::tick(unsigned int time) {

    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
        if (!fVehicles[i]->setNewPosition(time)) {
            fVehicles[i]->setCurrentRoad(NULL);
        } else if (fVehicles[i] != NULL) {
            fVehicles[i]->setAcceleration(
                    fVehicles[i]->getAcceleration(get_vehicle_on_road(fVehicles[i]->getCurrentRoad())));
        }
    }

    fVehicles.erase(std::remove_if(fVehicles.begin(), fVehicles.end(), test), fVehicles.end());//todo help
}

bool SimulationModel::properlyInitialized() {
    return _initCheck == this;
}

void SimulationModel::checkCollision(Vehicle *vehicle) {
    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
        if (fVehicles[i]->collides(vehicle) and vehicle != fVehicles[i])throw FatalException(vehicle_collision_error);
    }
}

void SimulationModel::addConnection(Road *from, Road *to) {
    if (to == NULL or !doesRoadExist(to->getName())) throw FatalException(road_non_ex_connection_to);
    if (from == NULL or !doesRoadExist(from->getName()))throw NonFatalException(road_non_ex_connection_from);
    from->addConnection(to);
}

void SimulationModel::automaticSimulation() {
    while (!fVehicles.empty()) {tick();
    }
}



