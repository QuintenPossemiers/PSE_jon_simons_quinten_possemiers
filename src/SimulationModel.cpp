#include "Vehicle.h"
#include "Exeptions/ParsingExc.h"

bool test(Vehicle *number) {
    return number->getCurrent_road() == NULL;
};

#include <iostream>
#include <algorithm>
#include "SimulationModel.h"

SimulationModel::SimulationModel() : _initCheck(this) {

};

void SimulationModel::add_road(Road *road) {
    if (does_road_exist(road->getName()) != NULL)
        throw ParsingExc(road_dupe_name);
    roads.push_back(road);
}

void SimulationModel::add_vehicle(Vehicle *vehicle) {

    if (NULL == does_road_exist(vehicle->getCurrent_road()->getName()))
        throw FatalException(non_existing_road);
    checkCollision(vehicle);

    vehicles.push_back(vehicle);
}


Road *SimulationModel::does_road_exist(std::string name) {
    for (unsigned int i = 0; i < roads.size(); ++i) {
        if (roads[i]->getName() == name) return roads[i];
    }
    return NULL;
}

const std::vector<Vehicle *> &SimulationModel::getVehicles() const {
    return vehicles;
}

void SimulationModel::start(const char *xml_path) {
    vehicles.clear();
    roads.clear();
    Parser parser = Parser(xml_path);
    parser.initialise_roads_and_vehicles(this);
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
    return roads;
}

std::vector<Vehicle *> SimulationModel::get_vehicle_on_road(Road *road) {
    std::vector<Vehicle *> vehicles_on_road;

    for (unsigned int i = 0; i < vehicles.size(); ++i)
        if (vehicles[i]->getCurrent_road() == road)vehicles_on_road.push_back(vehicles[i]);


    return vehicles_on_road;
}

void SimulationModel::tick(unsigned int time) {

    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        if (!vehicles[i]->set_new_position(time)) {
            vehicles[i]->setCurrent_road(NULL);
        } else if (vehicles[i] != NULL) {
            vehicles[i]->set_new_speed(
                    vehicles[i]->get_acceleration(get_vehicle_on_road(vehicles[i]->getCurrent_road())));
        }
    }

    vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(), test), vehicles.end());//todo help
}

bool SimulationModel::properlyInitialized() {
    return _initCheck == this;
}

void SimulationModel::checkCollision(Vehicle *vehicle) {
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i]->collides(vehicle) and vehicle != vehicles[i])throw FatalException(vehicle_collision_error);
    }
}

void SimulationModel::addConnection(Road *from, Road *to) {
    if (to == NULL or !does_road_exist(to->getName())) throw FatalException(road_non_ex_connection_to);
    if (from == NULL or !does_road_exist(from->getName()))throw ParsingExc(road_non_ex_connection_from);
    from->add_connection(to);
}

void SimulationModel::automaticSimulation() {
    while (!vehicles.empty()) {tick();
    }
}



