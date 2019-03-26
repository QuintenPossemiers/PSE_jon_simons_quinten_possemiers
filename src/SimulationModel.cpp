#include "Vehicle.h"

bool test (Vehicle *number) {
    return number == NULL;
};

#include <iostream>
#include <algorithm>
#include "SimulationModel.h"

SimulationModel::SimulationModel() {

};

void SimulationModel::add_road(Road *road) {
    roads.push_back(road);
}

void SimulationModel::add_vehicle(Vehicle *vehicle) {
    vehicles.push_back(vehicle);
}


Road *SimulationModel::does_road_exist(std::string name) {
    for (int i = 0; i < roads.size(); ++i) {
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

    for (int i = 0; i < model.getRoads().size(); ++i) {
        os << *model.getRoads()[i] << std::endl;
    }

    for (int j = 0; j < model.getVehicles().size(); ++j) {
        os << *model.getVehicles()[j] << std::endl;
    }
    return os;
}

const std::vector<Road *> &SimulationModel::getRoads() const {
    return roads;
}

std::vector<Vehicle *> SimulationModel::get_vehicle_on_road(Road *road) {
    std::vector<Vehicle *> vehicles_on_road;

    for (int i = 0; i < vehicles.size(); ++i)
        if (vehicles[i]->getCurrent_road() == road)vehicles_on_road.push_back(vehicles[i]);


    return vehicles_on_road;
}

void SimulationModel::tick(unsigned int time) {

    for (int i = 0; i < vehicles.size(); ++i) {
        if (!vehicles[i]->set_new_position(time)) {
            vehicles[i] = NULL;
        }
        if (vehicles[i] != NULL) {
            vehicles[i]->set_new_speed(
                    vehicles[i]->get_acceleration(get_vehicle_on_road(vehicles[i]->getCurrent_road())));
        }
    }

    vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(), test), vehicles.end());//todo help
}



