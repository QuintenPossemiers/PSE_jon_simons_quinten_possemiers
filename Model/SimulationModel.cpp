//
// Created by Quinten on 3/9/2019.
//

#include <iostream>
#include "SimulationModel.h"

SimulationModel::SimulationModel() = default;

void SimulationModel::add_road(Road *road) {
    roads.push_back(road);
}

void SimulationModel::add_vehicle(Vehicle *vehicle) {
    vehicles.push_back(vehicle);
}


Road* SimulationModel::does_road_exist(std::string name) {
    for (const auto &item : roads) {
        if (item->getName() == name) return item;
    }
    return nullptr;
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

