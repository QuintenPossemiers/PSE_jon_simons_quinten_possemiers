//
// Created by Quinten on 3/9/2019.
//


#include <lzma.h>
#include "Vehicle.h"

auto test = [](Vehicle *number) -> bool {
    return number == nullptr;
};

#include <iostream>
#include <algorithm>
#include "SimulationModel.h"

SimulationModel::SimulationModel() = default;

void SimulationModel::add_road(Road *road) {
    roads.push_back(road);
}

void SimulationModel::add_vehicle(Vehicle *vehicle) {
    vehicles.push_back(vehicle);
}


Road *SimulationModel::does_road_exist(std::string name) {
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

std::ostream &operator<<(std::ostream &os, const SimulationModel &model) {
    for (const auto &item : model.getRoads()) {
        os << *item << std::endl;
    }
    for (const auto &getVehicle : model.getVehicles()) {
        os << *getVehicle << std::endl;
    }
    return os;
}

const std::vector<Road *> &SimulationModel::getRoads() const {
    return roads;
}

std::vector<Vehicle *> SimulationModel::get_vehicle_on_road(Road *road) {
    std::vector<Vehicle *> vehicles_on_road;
    for (const auto &item : vehicles) {
        if (item->getCurrent_road() == road)vehicles_on_road.push_back(item);
    }

    return vehicles_on_road;
}

void SimulationModel::tick(unsigned int time) {
    for (auto &item : vehicles) {
        if (!item->set_new_position(time)) {
            item = nullptr;
        }
        if (item != nullptr){
        item->set_new_speed(item->get_acceleration(get_vehicle_on_road(item->getCurrent_road())));
        }
    }
    vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(), test), vehicles.end());
}



