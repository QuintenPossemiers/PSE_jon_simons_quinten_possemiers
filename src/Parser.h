
class SimulationModel;

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <string>
#include <vector>
#include "Road.h"
#include "Vehicle.h"
#include "SimulationModel.h"
#include "../TinyXml/tinyxml.h"

static std::string gConnectionDelimiter = "::"; //required size == 2
class Parser {

private:
    const char *kXmlPath;
public:

    explicit Parser(const char *kXmlPath);
private:

    void initialiseRoads(TiXmlElement *roadElements, SimulationModel *simulationModel,
                         std::vector<std::string> &connections);

    void initialiseVehicles(TiXmlElement *vehicleElements, SimulationModel *simulationModel);

    void initialiseConnections(SimulationModel *simulationModel, std::vector<std::string> &connections);

public:
    void initialiseRoadsAndVehicles(SimulationModel *simulationModel);
    /*!
     * Fills simulation model with data from the file!
     * @param simulationModel pointer to current simulation model
     */

};


#endif //UNTITLED_PARSER_H
