
#include <bits/ios_base.h>
#include <iostream>
#include "Parser.h"
#include "Exeptions/AllExceptions.h"
#include "Exeptions/ParsingExc.h"

Parser::Parser(const char *xml_path) : xml_path(xml_path) {}

void Parser::initialise_roads_and_vehicles(SimulationModel *simulationModel) {

    TiXmlDocument doc;
    TiXmlElement *root;

    //Open the file and throw an error message if the file could not be found!
    if (!doc.LoadFile(xml_path)) throw ParsingExc(file_opening_error);;

    //Initialise the root of the xml file and check if it is not a null pointer
    root = doc.FirstChildElement();
    if (root == NULL) throw ParsingExc(file_root);

    std::vector<std::string> connections;
    initialise_roads(root->FirstChildElement("BAAN"), simulationModel, connections);
    initialise_connections(simulationModel, connections);
    initialise_vehicles(root->FirstChildElement("VOERTUIG"), simulationModel);

    doc.Clear();

}

void Parser::initialise_roads(TiXmlElement *elements_of_roads, SimulationModel *simulationModel,
                              std::vector<std::string> &connections) {
    for (TiXmlElement *road = elements_of_roads; road != NULL; road = road->NextSiblingElement("BAAN")) {
        try {
            std::string name = road->FirstChildElement("naam")->GetText();
            unsigned int speed_limit =
                    static_cast<unsigned int>(std::atoi(road->FirstChildElement("snelheidslimiet")->GetText()));
            unsigned int length = static_cast<unsigned int>(std::atoi(road->FirstChildElement("lengte")->GetText()));
            for (TiXmlElement *connection = road->FirstChildElement("verbinding"); connection != NULL;
                 connection->NextSiblingElement("verbinding")) {
                connections.push_back(connection->GetText());
            }
            if (simulationModel->does_road_exist(name) != NULL)
                throw ParsingExc(road_dupe_name);
            for (int i = 0; i < connections.size(); ++i) {
                connections[i].append(connection_delimiter);
                connections[i].append(name);
            }
            simulationModel->add_road(new Road(name, speed_limit, length));
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Parser::initialise_vehicles(TiXmlElement *elements_of_vehicles, SimulationModel *simulationModel) {
    for (TiXmlElement *element = elements_of_vehicles; element != NULL;
         element = element->NextSiblingElement("VOERTUIG")) {
        std::string type, license_plate, road_name;
        double position = 0;
        unsigned int speed = 0;
        try {
            type = element->FirstChildElement("type")->GetText();
            license_plate = element->FirstChildElement("nummerplaat")->GetText();
            road_name = element->FirstChildElement("baan")->GetText();
            position = std::strtod(element->FirstChildElement("positie")->GetText(), NULL);

            std::string speed_str = element->FirstChildElement("snelheid")->GetText();
            char * writable = new char[speed_str.size() + 1];
            char **speed_ptr = &writable;
            std::copy(speed_str.begin(), speed_str.end(), writable);

            speed = static_cast<unsigned int>(std::strtol(
                    writable,speed_ptr, 10));
        } catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
//check if road exists
        Road *road = simulationModel->does_road_exist(road_name);

//check collisions
         for (int i = 0; i < simulationModel->getVehicles().size(); ++i) {
            if (simulationModel->getVehicles()[i]->collides(position, road_name)) {
                throw ParsingExc(vehicle_collision_error);
            }
        }
        if (road != NULL)
            simulationModel->add_vehicle(new Vehicle(speed,position,license_plate,road,new VehicleType(type)));
        else throw ParsingExc(non_existing_road);
    }
}


void Parser::initialise_connections(SimulationModel *simulationModel, std::vector<std::string> &connections) {
    for (int i = 0; i < connections.size(); ++i) {
        Road *road_from = simulationModel->does_road_exist(
                connections[i].substr(connections[i].find(connection_delimiter) + 2, connections[i].size() - 1));
        Road *road_to = simulationModel->does_road_exist(connections[i].substr(0,
                connections[i].find(connection_delimiter)));
        if (road_from != NULL and road_to != NULL) road_from->add_connection(road_to);
        else if (!road_from) throw ParsingExc(road_non_ex_connection_from);
        else throw ParsingExc(road_non_ex_connection_to);
    }

}

