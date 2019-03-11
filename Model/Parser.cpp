
#include <bits/ios_base.h>
#include <iostream>
#include "Parser.h"
#include "Exeptions/AllExceptions.h"
#include "Exeptions/ParsingExc.h"

Parser::Parser(const char *xml_path) :xml_path(xml_path){}

void Parser::initialise_roads_and_vehicles(SimulationModel *simulationModel) {

    TiXmlDocument doc;
    TiXmlElement *root;
    int rejected_tag_count = 0;

    //Open the file and throw an error message if the file could not be found!
    if (!doc.LoadFile(xml_path)) throw ParsingExc(ParsingErr::dumb);;

    //Initialise the root of the xml file and check if it is not a null pointer
    root = doc.FirstChildElement();
    if (root == nullptr) throw ParsingExc(ParsingErr::file_root);


    std::vector<TiXmlElement *> elements_of_roads;
    std::vector<TiXmlElement *> elements_of_vehicles;

    for (TiXmlElement *element = root->FirstChildElement();             //Loop over all tags should only contain
         element != nullptr; element = element->NextSiblingElement()) { //Either "BAAN" or "VOERTUIG"
        try {
            if (element->FirstChild() != nullptr) {
                std::string element_name = element->Value();
                if (element_name == "BAAN") elements_of_roads.push_back(element);
                else if (element_name == "VOERTUIG") elements_of_vehicles.push_back(element);
                else {
                    rejected_tag_count++;       //todo If the tag does contain something else it wont be processed!
                    throw ParsingExc(ParsingErr::xml_expected_tag);
                }
            }
        } catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    initialise_roads(elements_of_roads, simulationModel);
    initialise_vehicles(elements_of_vehicles, simulationModel);

    doc.Clear();

}

void Parser::initialise_roads(std::vector<TiXmlElement *> elements_of_roads, SimulationModel *simulationModel) {
    for (const auto &road : elements_of_roads) {
        std::string name;
        unsigned int speed_limit = 0, length = 0;
        try {
            for (TiXmlElement *attribute = road->FirstChildElement();
                 attribute != nullptr; attribute = attribute->NextSiblingElement()) {
                std::string attribute_name = attribute->Value();
                if (attribute_name == "naam")name = attribute->GetText();
                else if (attribute_name == "snelheidslimiet")
                    speed_limit = static_cast<unsigned int>(std::stoi(attribute->GetText()));
                else if (attribute_name == "lengte")
                    length = static_cast<unsigned int>(std::stoi(attribute->GetText()));
            }
            if (simulationModel->does_road_exist(name) != nullptr)
                throw ParsingExc(ParsingErr::road_dupe_name);
            simulationModel->add_road(new Road(name, speed_limit, length));
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }

    }

}

void
Parser::initialise_vehicles(std::vector<TiXmlElement *> elements_of_vehicles, SimulationModel *simulationModel) {
    for (auto element  :elements_of_vehicles) {
        std::string type, license_plate, road_name;
        unsigned int position = 0, speed = 0;

        for (TiXmlElement *attribute = element->FirstChildElement();
             attribute != nullptr; attribute = attribute->NextSiblingElement()) {
            std::string element_name = attribute->Value();

            if (element_name == "type")type = attribute->GetText();
            else if (element_name == "nummerplaat")license_plate = attribute->GetText();
            else if (element_name == "baan")road_name = attribute->GetText();
            else if (element_name == "positie")
                position = static_cast<unsigned int>(std::stoi(attribute->GetText()));
            else if (element_name == "snelheid")speed = static_cast<unsigned int>(std::stoi(attribute->GetText()));
        }

        //check if road exists
        Road *road = simulationModel->does_road_exist(road_name);
        //check collisions
        try {
            for (const auto &item : simulationModel->getVehicles()) {
                if (item->collides(position, road_name)) {
                    throw ParsingExc(ParsingErr::vehicle_collision_error);
                }
            }
            if (road != nullptr)
                simulationModel->add_vehicle(new Vehicle(speed, position, license_plate, type, road));
            else throw ParsingExc(ParsingErr::non_existing_road);
        } catch (ParsingExc &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

