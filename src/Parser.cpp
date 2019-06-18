
#include <bits/ios_base.h>
#include <iostream>
#include <sstream>
#include "Parser.h"
#include <list>
#include "Exceptions.h"

Parser::Parser(const char *kXmlPath) : kXmlPath(kXmlPath), _initCheck(this) {
    ENSURE(properlyInitialized(), "parser niet succesvol");
}

void Parser::initialiseRoadsAndVehicles(SimulationModel *simulationModel) {
    REQUIRE(simulationModel != NULL, "Ongeldig simulatie model!");

    TiXmlDocument doc;
    TiXmlElement *root;

    //Open the file and throw an error message if the file could not be found!
    if (!doc.LoadFile(kXmlPath)) {
        std::stringstream ss;
        ss << doc.ErrorDesc();
        ss << " @row: ";
        ss << doc.ErrorRow();

        throw FatalException(ss.str());
    }

    //Initialise the root of the xml file and check if it is not a null pointer
    root = doc.FirstChildElement();
    if (root == NULL)throw NonFatalException(file_root);

    std::vector<std::string> connections;
    initialiseRoads(root->FirstChildElement("BAAN"), simulationModel, connections);
    initialiseConnections(simulationModel, connections);
    initialiseVehicles(root->FirstChildElement("VOERTUIG"), simulationModel);
    initialiseSigns(root->FirstChildElement("VERKEERSTEKEN"), simulationModel);
    doc.Clear();

}

void Parser::initialiseRoads(TiXmlElement *roadElements, SimulationModel *simulationModel,
                             std::vector<std::string> &connections) {
    unsigned int currentIndex = 0;
    for (TiXmlElement *road = roadElements; road != NULL; road = road->NextSiblingElement("BAAN")) {
        try {
            std::string name = road->FirstChildElement("naam")->GetText();
            unsigned int speedLimit =
                    static_cast<unsigned int>(std::atoi(road->FirstChildElement("snelheidslimiet")->GetText()));
            unsigned int length = static_cast<unsigned int>(std::atoi(road->FirstChildElement("lengte")->GetText()));

            unsigned int strokes = 2;

            if (road->FirstChildElement("rijstroken") != NULL) {
                strokes = static_cast<unsigned int>(std::atoi(road->FirstChildElement("rijstroken")->GetText()));
            }


            simulationModel->addRoad(new Road(name, speedLimit, length, strokes));

            for (TiXmlElement *connection = road->FirstChildElement("verbinding"); connection != NULL;
                 connection = connection->NextSiblingElement("verbinding")) {
                connections.push_back(connection->GetText());
            }
            for (unsigned int i = currentIndex; i < connections.size(); ++i) {
                connections[i].append(gConnectionDelimiter);
                connections[i].append(name);
            }
            currentIndex = (unsigned int) connections.size();
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
            type = element->FirstChildElement("type")->GetText();
            licensePlate = element->FirstChildElement("nummerplaat")->GetText();
            roadName = element->FirstChildElement("baan")->GetText();
            position = (unsigned int) std::atoi(element->FirstChildElement("positie")->GetText());

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
            Vehicle *newVehicle = NULL;
            if (type == "AUTO" || type == "auto") newVehicle = new Car(speed, position, licensePlate, road);
            else if (type == "bus" || type == "BUS") newVehicle = new Bus(speed, position, licensePlate, road);
            else if (type == "MOTORFIETS" || type == "motorfiets")
                newVehicle = new Motorcycle(speed, position, licensePlate, road);
            else if (type == "vrachtwagen" || type == "VRACHTWAGEN")
                newVehicle = new Truck(speed, position, licensePlate, road);
            else break;


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

bool Parser::properlyInitialized() {
    return _initCheck == this;
}

void Parser::initialiseSigns(TiXmlElement *signElements, SimulationModel *simulationModel) {
    //unsigned int currentIndex = 0;
    for (TiXmlElement *signElement = signElements;
         signElement != NULL; signElement = signElement->NextSiblingElement("VERKEERSTEKEN")) {
        try {
            std::string street = signElement->FirstChildElement("baan")->GetText();

            unsigned int position = static_cast<unsigned int>(std::atoi(
                    signElement->FirstChildElement("positie")->GetText()));

            std::string type = signElement->FirstChildElement("type")->GetText();

            if (type == "BUSHALTE") {
                simulationModel->addBusStopToRoad(street, position);
            } else if (type == "VERKEERSLICHT") {
                simulationModel->addTraffiLightToRoad(street, position);
            } else if (type == "ZONE") {
                unsigned int speedLimit =
                        static_cast<unsigned int>(std::atoi(
                                signElement->FirstChildElement("snelheidslimiet")->GetText()));
                simulationModel->addZoneToRoad(street, speedLimit, position);
            }


        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}


