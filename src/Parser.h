
class SimulationModel;

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <string>
#include <vector>
#include "Road.h"
#include "Vehicle.h"
#include "SimulationModel.h"
#include "DesignByContract.h"
#include "../TinyXml/tinyxml.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

static std::string gConnectionDelimiter = "::"; //required size == 2
class Parser {

private:
    Parser* _initCheck;
public:

    explicit Parser();
    //ENSURE(properlyInitialized(),"parser niet succesful");
private:

    enum SuccessEnum initialiseRoads(TiXmlElement *roadElements, SimulationModel *simulationModel,
                         std::vector<std::string> &connections, std::ostream& errStream);

    enum SuccessEnum initialiseVehicles(TiXmlElement *vehicleElements, SimulationModel *simulationModel, std::ostream& errStream);

    enum SuccessEnum initialiseConnections(SimulationModel *simulationModel, std::vector<std::string> &connections, std::ostream& errStream);

    enum SuccessEnum initialiseSigns(TiXmlElement *signElements, SimulationModel *simulationModel, std::ostream& errStream);

    const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream);

    bool isNumeric(const std::string& s);


public:
    enum SuccessEnum initialiseRoadsAndVehicles(SimulationModel *simulationModel, const char *kXmlPath, std::ostream& errStream);
    /*!
     * Fills simulation model with data from the file!
     * @param simulationModel pointer to current simulation model
     */
    //REQUIRE(simulationModel != NULL, "Ongeldig simulatie model!")
public:
    bool properlyInitialized();
    /*!
     *Checkt of parser goed geinitialiseerd is!
     *@return bool is het goed geinitialiseerd of niet
     **/

};


#endif //UNTITLED_PARSER_H
