
#include <bits/ios_base.h>
#include <iostream>
#include <sstream>
#include "Parser.h"
#include <list>
#include "Exceptions.h"

Parser::Parser() : _initCheck(this) {
    ENSURE(properlyInitialized(), "parser niet succesvol");
}

enum SuccessEnum
Parser::initialiseRoadsAndVehicles(SimulationModel *simulationModel, const char *kXmlPath, std::ostream &errStream) {
    REQUIRE(simulationModel != NULL, "Ongeldig simulatie model!");

    simulationModel->getVehicles().clear();
    simulationModel->getRoads().clear();

    TiXmlDocument doc;
    SuccessEnum endResult = Success;
    SuccessEnum p1 = Success, p2 = Success, p3 = Success, p4 = Success;
    //Open the file and throw an error message if the file could not be found!
    if (!doc.LoadFile(kXmlPath)) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << std::endl;
        return ImportAborted;
    }

    std::vector<std::string> connections;

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *test = doc.FirstChildElement();
         test != NULL; test = root->NextSiblingElement()) {
        std::string x = fetch_text(test, errStream);
        if (x != "BAAN" and x != "VOERTUIG" and x != "VERKEERSTEKEN" and !x.empty()) {
            errStream
                    << "Partial import: Expected :<BAAN> ... </BAAN>. or <VOERTUIG> ... </VOERTUIG>. or <VERKEERSTEKEN> ... </VERKEERSTEKEN>.\n";
        }
    }

    std::string rootName = root->Value();
    if (rootName != "root") {
        errStream << "XML PARTIAL IMPORT: Expected <root> ... </root> and got <"
                  << rootName << "> ... </" << rootName << ">." << std::endl;
        endResult = PartialImport;
    } else {
        TiXmlElement *banen, *voertuigen, *verkeerstekens;
        std::string sBanen, sVoertuigen, sVerkeerstekens;

        banen = root->FirstChildElement("BAAN");
        voertuigen = root->FirstChildElement("VOERTUIG");
        verkeerstekens = root->FirstChildElement("VERKEERSTEKEN");

        if (banen == NULL) {
            errStream << "XML PARTIAL IMPORT: Expected " << std::endl;
            endResult = PartialImport;

        } else {
            p1 = initialiseRoads(banen, simulationModel, connections, errStream);
        }
        if (voertuigen == NULL) {
            errStream << "XML PARTIAL IMPORT: Expected <VOERTUIG> ... </VOERTUIG>." << std::endl;
            endResult = PartialImport;
        } else {
            p2 = initialiseVehicles(voertuigen, simulationModel, errStream);
        }
        p3 = initialiseConnections(simulationModel, connections, errStream);
        p4 = initialiseSigns(verkeerstekens, simulationModel, errStream);
    }
    doc.Clear();
    if (p1 == ImportAborted or p2 == ImportAborted or p3 == ImportAborted or p4 == ImportAborted or
        endResult == ImportAborted)
        return ImportAborted;
    if (p1 == PartialImport or p2 == PartialImport or p3 == PartialImport or p4 == PartialImport or
        endResult == PartialImport)
        return PartialImport;

    return endResult;
}

enum SuccessEnum Parser::initialiseRoads(TiXmlElement *roadElements, SimulationModel *simulationModel,
                                         std::vector<std::string> &connections, std::ostream &errStream) {
    unsigned int currentIndex = 0;
    enum SuccessEnum returnVal = Success;
    for (TiXmlElement *road = roadElements; road != NULL; road = road->NextSiblingElement("BAAN")) {

        std::string name = fetch_text(road->FirstChildElement("naam"), errStream);
        std::string speedLimit = fetch_text(road->FirstChildElement("snelheidslimiet"), errStream);
        std::string length = fetch_text(road->FirstChildElement("lengte"), errStream);
        std::string strokes = fetch_text(road->FirstChildElement("rijstroken"), errStream);


        try {


            if (!isNumeric(speedLimit)) {
                returnVal = PartialImport;
                errStream << "Snelheidslimiet moet numeriek zijn! dus niet: " << speedLimit << std::endl;
            }
            if (!isNumeric(length)) {
                returnVal = PartialImport;
                errStream << "lengte moet numeriek zijn! dus niet: " << length << std::endl;
            }
            if (isNumeric(speedLimit) and isNumeric(length)) {

                simulationModel->addRoad(new Road(name,
                                                  static_cast<unsigned int>(std::atoi(speedLimit.c_str())),
                                                  static_cast<unsigned int>(std::atoi(length.c_str())),
                                                  strokes.empty() ? 1 : static_cast<unsigned int>(std::atoi(
                                                          strokes.c_str()))));
            }
        } catch (const std::invalid_argument &e) {
            returnVal = PartialImport;
            errStream << e.what() << std::endl;
        }

        for (TiXmlElement *connection = road->FirstChildElement("verbinding"); connection != NULL;
             connection = connection->NextSiblingElement("verbinding")) {
            connections.push_back(connection->GetText());
        }
        for (unsigned int i = currentIndex; i < connections.size(); ++i) {
            connections[i].append(gConnectionDelimiter);
            connections[i].append(name);
        }
        currentIndex = (unsigned int) connections.size();

    }
    return returnVal;
}

const std::string Parser::fetch_text(TiXmlNode *pElement, std::ostream &errStream) {
    {
        if (pElement == NULL) return "";
        TiXmlNode *elemNode = pElement->FirstChild();
        if (elemNode == NULL) return "";
        TiXmlText *text = elemNode->ToText();
        if (text == NULL) return "";
        return text->Value();
    }
}

enum SuccessEnum
Parser::initialiseVehicles(TiXmlElement *vehicleElements, SimulationModel *simulationModel, std::ostream &errStream) {
    enum SuccessEnum returnVal = Success;

    for (TiXmlElement *element = vehicleElements; element != NULL;
         element = element->NextSiblingElement("VOERTUIG")) {


        std::string type = fetch_text(element->FirstChildElement("type"), errStream);
        std::string licensePlate = fetch_text(element->FirstChildElement("nummerplaat"), errStream);
        std::string roadName = fetch_text(element->FirstChildElement("baan"), errStream);
        std::string position = fetch_text(element->FirstChildElement("positie"), errStream);
        std::string speed_str = fetch_text(element->FirstChildElement("snelheid"), errStream);

//            char *writable = new char[speed_str.size() + 1];
//            char **speed_ptr = &writable;
//            std::copy(speed_str.begin(), speed_str.end(), writable);
//
//            speed = static_cast<unsigned int>(std::strtol(
//                    writable, speed_ptr, 10));


        Road *road = simulationModel->doesRoadExist(roadName);
        if (road != NULL) {
            try {
                if (!isNumeric(speed_str)) {
                    returnVal = PartialImport;
                    errStream << "Snelheid moet numeriek zijn! dus niet: " << speed_str << std::endl;
                }
                if (!isNumeric(position)) {
                    returnVal = PartialImport;
                    errStream << "Position moet numeriek zijn! dus niet: " << position << std::endl;
                }
                bool typecheck = true;
                if (type != "AUTO" and type != "BUS" and type != "MOTORFIETS" and type != "VRACHTWAGEN") {
                    returnVal = PartialImport;
                    errStream << "Voertuig moet van type MOTORFIETS, VRACHTWAGEN BUS of AUTO zijn dus niet: " << type
                              << std::endl;
                    typecheck = false;
                }
                if (isNumeric(position) and isNumeric(speed_str) and typecheck) {


                    Vehicle *newVehicle = NULL;
                    if (type == "AUTO" || type == "auto")
                        newVehicle = new Car(
                                static_cast<unsigned int>(std::atoi(speed_str.c_str())),
                                static_cast<unsigned int>(std::atoi(position.c_str())),
                                licensePlate,
                                road);
                    else if (type == "bus" || type == "BUS")
                        newVehicle = new Bus(static_cast<unsigned int>(std::atoi(speed_str.c_str())),
                                             static_cast<unsigned int>(std::atoi(position.c_str())),
                                             licensePlate,
                                             road);
                    else if (type == "MOTORFIETS" || type == "motorfiets")
                        newVehicle = new Motorcycle(static_cast<unsigned int>(std::atoi(speed_str.c_str())),
                                                    static_cast<unsigned int>(std::atoi(position.c_str())),
                                                    licensePlate,
                                                    road);
                    else if (type == "vrachtwagen" || type == "VRACHTWAGEN")
                        newVehicle = new Truck(static_cast<unsigned int>(std::atoi(speed_str.c_str())),
                                               static_cast<unsigned int>(std::atoi(position.c_str())),
                                               licensePlate,
                                               road);
                    else break;


                    simulationModel->checkCollision(newVehicle);
                    simulationModel->addVehicle(newVehicle);
                }
            } catch (const std::invalid_argument &e) {
                returnVal = PartialImport;
                errStream << e.what() << std::endl;
            }
        } else {
            returnVal = PartialImport;
            errStream << "Partial import: adding vehicle to non existing road: " << roadName << "\n";
        }
    }
    return returnVal;
}


enum SuccessEnum
Parser::initialiseConnections(SimulationModel *simulationModel, std::vector<std::string> &connections,
                              std::ostream &errStream) {
    enum SuccessEnum returnVal = Success;
    for (unsigned int i = 0; i < connections.size(); ++i) {
        Road *road_from = simulationModel->doesRoadExist(
                connections[i].substr(connections[i].find(gConnectionDelimiter) + 2, connections[i].size() - 1));
        Road *road_to = simulationModel->doesRoadExist(connections[i].substr(0,
                                                                             connections[i].find(
                                                                                     gConnectionDelimiter)));
        if (road_from != NULL) road_from->addConnection(road_to);
        else {
            returnVal = PartialImport;
            errStream << "Partial Import connection was invalid: from "
                      << connections[i].substr(connections[i].find(gConnectionDelimiter) + 2, connections[i].size() - 1)
                      << " to " << connections[i].substr(0,
                                                         connections[i].find(
                                                                 gConnectionDelimiter));
        }
    }
    return returnVal;
}

bool Parser::properlyInitialized() {
    return _initCheck == this;
}

enum SuccessEnum
Parser::initialiseSigns(TiXmlElement *signElements, SimulationModel *simulationModel, std::ostream &errStream) {
    enum SuccessEnum returnVal = Success;
    for (TiXmlElement *signElement = signElements;
         signElement != NULL; signElement = signElement->NextSiblingElement("VERKEERSTEKEN")) {

        std::string street = fetch_text(signElement->FirstChildElement("baan"), errStream);
        std::string position = fetch_text(signElement->FirstChildElement("positie"), errStream);
        std::string type = fetch_text(signElement->FirstChildElement("type"), errStream);
        std::string speedlimit = fetch_text(signElement->FirstChildElement("snelheidslimiet"), errStream);

        if (!isNumeric(speedlimit)) {
            returnVal = PartialImport;
            errStream << "Snelheid moet numeriek zijn! dus niet: " << speedlimit << std::endl;
        }
        if (!isNumeric(position)) {
            returnVal = PartialImport;
            errStream << "Position moet numeriek zijn! dus niet: " << position << std::endl;
        }

        if (type == "BUSHALTE" or type == "VERKEERSLICHT" or type == "ZONE") {
            if (isNumeric(position) and isNumeric(speedlimit)) {
                try {
                    if (type == "BUSHALTE") {
                        simulationModel->addBusStopToRoad(street,
                                                          static_cast<unsigned int>(std::atoi(position.c_str())));
                    } else if (type == "ZONE") {
                        simulationModel->addZoneToRoad(street, static_cast<unsigned int>(std::atoi(speedlimit.c_str())),
                                                       static_cast<unsigned int>(std::atoi(position.c_str())));
                    }
                    if (type == "VERKEERSLICHT") {
                        simulationModel->addTraffiLightToRoad(street,
                                                              static_cast<unsigned int>(std::atoi(position.c_str())));
                    }

                } catch (const std::invalid_argument &e) {
                    returnVal = PartialImport;
                    errStream << e.what() << std::endl;
                }
            }

        } else {
            returnVal = PartialImport;
            errStream << "Partial import: type \"" << type << "\" bestaat niet.\n";
        }


    }
    return returnVal;
}

bool Parser::isNumeric(const std::string &test) {
    std::string::const_iterator it = test.begin();
    while (it != test.end()) {
        if (!std::isdigit(*it))
            return false;
        ++it;
    }
    return true;
}


