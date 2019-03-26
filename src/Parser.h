
class SimulationModel;

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <string>
#include <vector>
#include "Road.h"
#include "Vehicle.h"
#include "SimulationModel.h"
#include "../TinyXml/tinyxml.h"

static std::string connection_delimiter = "::"; //required size == 2
class Parser {

    /**section reserved for variables*/
private:
    const char *xml_path;




    /**section reserved for the constructor and destructor
     *
     * The constructor requires only a path to the xml file
     * */
public:

    explicit Parser(const char *xml_path);

    /**section reserved for private functions*/
private:

    void initialise_roads(TiXmlElement * elements_of_roads, SimulationModel *simulationModel, std::vector<std::string> &connections);

    void initialise_vehicles(TiXmlElement * elements_of_vehicles, SimulationModel *simulationModel);

    void initialise_connections(SimulationModel *simulationModel, std::vector<std::string> &connections);

    /**section reserved for public functions*/
public:
    void initialise_roads_and_vehicles(SimulationModel *simulationModel);

};


#endif //UNTITLED_PARSER_H