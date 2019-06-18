#include "Vehicle.h"
#include "Exceptions.h"
#include <fstream>
#include <list>


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
    if (doesRoadExist(road->getName()) != NULL)
        throw NonFatalException(road_dupe_name);
    fRoads.push_back(road);
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

void SimulationModel::printToFile(const std::string &fileName) {
    REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    std::ofstream myfile;
    myfile.open(fileName.c_str());
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
//    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
//        if (!fVehicles[i]->updatePosition()) {
//            fVehicles[i]->leaveRoad();
//        } else if (fVehicles[i] != NULL) {
//            fVehicles[i]->updateSpeed();
//        }
//    }

    for (unsigned int i = fVehicles.size() - 1; i < (unsigned int) -1; --i) {
        if (!fVehicles[i]->updatePosition()) {
            fVehicles[i]->leaveRoad();
        }
    }
    for (unsigned int i = fVehicles.size() - 1; i < (unsigned int) -1; --i) {
        if (fVehicles[i]->getFCurrentRoad() != NULL) {
            fVehicles[i]->updateSpeed();
        }
    }
    for (unsigned int j = 0; j < fRoads.size(); ++j) {
        fRoads[j]->tickVerkeersLichten();
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
    if (from == NULL or !doesRoadExist(from->getName()))throw NonFatalException(road_non_ex_connection_from);
    from->addConnection(to);
}

void SimulationModel::automaticSimulation() {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    while (!fVehicles.empty()) {
        tick();
    }
    ENSURE(fVehicles.empty(), "simulatie mislukt");
}

void SimulationModel::addZoneToRoad(std::string &name, unsigned int speedLimit, unsigned int position) {
    REQUIRE(properlyInitialized(), "simulatie model niet geinitialiseerd");
    Road *road = getRoad(name);
    if (road == NULL)
        return;
    road->addZone(position, speedLimit);
}

void SimulationModel::addBusStopToRoad(std::string &name, unsigned int position) {
    REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    Road *road = getRoad(name);
    if (road == NULL)
        return;
    road->addBusStop(position);
}


Road *SimulationModel::getRoad(std::string &name) {
    for (unsigned int i = 0; i < fRoads.size(); ++i) {
        if (fRoads[i]->getName() == name) return fRoads[i];
    }
    return NULL;
}

void SimulationModel::addTraffiLightToRoad(std::string &name, unsigned int position) {
    REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    Road *road = getRoad(name);
    if (road == NULL)
        return;
    road->addTrafficLight(position);
}


template<class T>
struct ptr_comparison {
    bool operator()(T *a, T *b) { return *a < *b; }
};

void SimulationModel::sort() {
    REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    std::list<Vehicle *> list1;
    for (unsigned int j = 0; j < this->getVehicles().size(); ++j) {
        fVehicles[j]->setFNextVehicle(NULL);
        fVehicles[j]->setFPrevVehicle(NULL);
        list1.push_back(fVehicles[j]);
    }
    list1.sort(ptr_comparison<Vehicle>());
    fVehicles.clear();
    fVehicles.insert(fVehicles.begin(), list1.begin(), list1.end());
    for (unsigned int i = 0; i < fVehicles.size(); ++i) {
        fVehicles[i]->setFPrevVehicle(i == fVehicles.size() - 1 ? NULL : fVehicles[i + 1]);
        fVehicles[i]->setFNextVehicle(i == 0 ? NULL : fVehicles[i - 1]);
    }
}








