#include "Vehicle.h"
#include "Exceptions.h"
#include <fstream>


bool test(Vehicle *number) {
    return number->getFCurrentRoad() == NULL;
};

#include <iostream>
#include <algorithm>
#include "SimulationModel.h"

SimulationModel::SimulationModel() : _initCheck(this) {
    ENSURE(properlyInitialized(), "simulatie model niet geinitialiseerd");
};

void SimulationModel::addRoad(Road *road) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    REQUIRE(road != NULL, "geen geldige baan");
    unsigned int i = (unsigned int) fRoads.size() + 1;
    if (doesRoadExist(road->getName()) != NULL)
        throw NonFatalException(road_dupe_name);
    fRoads.push_back(road);
    ENSURE(fRoads.size() == i, "baan niet toegevoegd");
}

void SimulationModel::addVehicle(Vehicle *vehicle) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    REQUIRE(vehicle != NULL, "geen geldig voertuig");
    unsigned int i = (unsigned int) fVehicles.size() + 1;
    if (NULL == doesRoadExist(vehicle->getFCurrentRoad()->getName()))
        throw FatalException(non_existing_road);
    checkCollision(vehicle);
    fVehicles.push_back(vehicle);
    ENSURE(fVehicles.size() == i, "voertuig niet toegevoegd");
}

void SimulationModel::printToFile(const std::string &fileName){
    std::ofstream myfile;
    myfile.open (fileName.c_str());
    myfile << *this;
    myfile.close();
};


Road *SimulationModel::doesRoadExist(std::string name) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    for (unsigned int i = 0; i < fRoads.size(); ++i) {
        if (fRoads[i]->getName() == name) return fRoads[i];
    }
    return NULL;
}

std::vector<Vehicle *> &SimulationModel::getVehicles() {
    return fVehicles;
}

void SimulationModel::start(const char *xml_path) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    fVehicles.clear();
    fRoads.clear();
    Parser parser = Parser(xml_path);
    parser.initialiseRoadsAndVehicles(this);
}

std::ostream &operator<<(std::ostream &os, SimulationModel &model) {
    REQUIRE(model.properlyInitialized(), "simulatie model niet geinitialiseerd");
    for (unsigned int i = 0; i < model.getRoads().size(); ++i) {
        os << *model.getRoads()[i] << std::endl;
    }

    for (unsigned int j = 0; j < model.getVehicles().size(); ++j) {
        os << *model.getVehicles()[j] << std::endl;
    }
    return os;
}

std::vector<Road *> &SimulationModel::getRoads() {
    return fRoads;
}

std::vector<Vehicle *> SimulationModel::get_vehicle_on_road(Road *road) {
    std::vector<Vehicle *> vehiclesOnRoad;

    for (unsigned int i = 0; i < fVehicles.size(); ++i)
        if (fVehicles[i]->getFCurrentRoad() == road)vehiclesOnRoad.push_back(fVehicles[i]);


    return vehiclesOnRoad;
}

void SimulationModel::tick(unsigned int time) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
        if (!fVehicles[i]->setNewPosition()) {
            fVehicles[i]->leaveRoad();
        } else if (fVehicles[i] != NULL) {
            fVehicles[i]->updateSpeed();
        }
    }

    fVehicles.erase(std::remove_if(fVehicles.begin(), fVehicles.end(), test), fVehicles.end());
}

bool SimulationModel::properlyInitialized() {
    return _initCheck == this;
}

void SimulationModel::checkCollision(Vehicle *vehicle) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    REQUIRE(vehicle != NULL, "geen geldig voertuig");
    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
        if (fVehicles[i]->collides(vehicle) and vehicle != fVehicles[i])throw FatalException(vehicle_collision_error);
    }
}

void SimulationModel::addConnection(Road *from, Road *to) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    REQUIRE(from != NULL, "geen geldige baan waarvan je vertrekt");
    REQUIRE(to != NULL, "geen geldige baan waar je naartoe gaat");
    if (to == NULL or !doesRoadExist(to->getName())) throw FatalException(road_non_ex_connection_to);
    unsigned int i = (unsigned int) from->getConnections().size() + 1;
    if (from == NULL or !doesRoadExist(from->getName()))throw NonFatalException(road_non_ex_connection_from);
    from->addConnection(to);
    ENSURE(from->getConnections().size() == i, "connectie niet toegevoegd");
}

void SimulationModel::automaticSimulation() {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    while (!fVehicles.empty()) {
        tick();
    }
    ENSURE(fVehicles.empty(), "simulatie mislukt");
}




