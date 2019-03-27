
#include <bits/ios_base.h>
#include <iostream>
#include "Parser.h"
#include "Exeptions/Exceptions.h"

Parser::Parser(const char *kXmlPath) : kXmlPath(kXmlPath) {}

void Parser::initialiseRoadsAndVehicles(SimulationModel *simulationModel) {

    TiXmlDocument doc;
    TiXmlElement *root;

    //Open the file and throw an error message if the file could not be found!
    if (!doc.LoadFile(kXmlPath)) throw NonFatalException(file_opening_error);

    //Initialise the root of the xml file and check if it is not a null pointer
    root = doc.FirstChildElement();
    if (root == NULL) throw NonFatalException(file_root);

    std::vector<std::string> connections;
    initialiseRoads(root->FirstChildElement("BAAN"), simulationModel, connections);
    initialiseConnections(simulationModel, connections);
    initialiseVehicles(root->FirstChildElement("VOERTUIG"), simulationModel);
    doc.Clear();

}

void Parser::initialiseRoads(TiXmlElement *roadElements, SimulationModel *simulationModel,
                             std::vector<std::string> &connections) {
    unsigned int currentIndex=0;
    for (TiXmlElement *road = roadElements; road != NULL; road = road->NextSiblingElement("BAAN")) {
        try {
            std::string name = road->FirstChildElement("naam")->GetText();
            unsigned int speedLimit =
                    static_cast<unsigned int>(std::atoi(road->FirstChildElement("snelheidslimiet")->GetText()));
            unsigned int length = static_cast<unsigned int>(std::atoi(road->FirstChildElement("lengte")->GetText()));


            simulationModel->addRoad(new Road(name, speedLimit, length));

            for (TiXmlElement *connection = road->FirstChildElement("verbinding"); connection != NULL;
                 connection = connection->NextSiblingElement("verbinding")) {
                connections.push_back(connection->GetText());
            }
            for (unsigned int i = currentIndex; i < connections.size(); ++i) {
                connections[i].append(gConnectionDelimiter);
                connections[i].append(name);
            }
            currentIndex = (unsigned int)connections.size();
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Parser::initialiseVehicles(TiXmlElement *vehicleElements, SimulationModel *simulationModel) {
    for (TiXmlElement *element = vehicleElements; element != NULL;
         element = element->NextSiblingElement("VOERTUIG")) {
        std::string type, licensePlate, roadName;
        unsigned int position = 0;
        unsigned int speed = 0;
        try {
            type = element->FirstChildElement("fType")->GetText();
            licensePlate = element->FirstChildElement("nummerplaat")->GetText();
            roadName = element->FirstChildElement("baan")->GetText();
            position = (unsigned int)std::atoi(element->FirstChildElement("positie")->GetText());

            std::string speed_str = element->FirstChildElement("snelheid")->GetText();
            char *writable = new char[speed_str.size() + 1];
            char **speed_ptr = &writable;
            std::copy(speed_str.begin(), speed_str.end(), writable);

            speed = static_cast<unsigned int>(std::strtol(
                    writable, speed_ptr, 10));
        } catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
//check if road exists
        Road *road = simulationModel->doesRoadExist(roadName);

//check collisions
        if (road != NULL) {
            Vehicle *newVehicle = new Vehicle(speed, position, licensePlate, road, new VehicleType(type));
            simulationModel->checkCollision(newVehicle);
            simulationModel->addVehicle(newVehicle);
        }
    }
}


void Parser::initialiseConnections(SimulationModel *simulationModel, std::vector<std::string> &connections) {
    for (unsigned int i = 0; i < connections.size(); ++i) {
        Road *road_from = simulationModel->doesRoadExist(
                connections[i].substr(connections[i].find(gConnectionDelimiter) + 2, connections[i].size() - 1));
        Road *road_to = simulationModel->doesRoadExist(connections[i].substr(0,
                                                                             connections[i].find(
                                                                                     gConnectionDelimiter)));
        if (road_from != NULL) road_from->addConnection(road_to);
        else throw NonFatalException(road_non_ex_connection_from);
    }

}

