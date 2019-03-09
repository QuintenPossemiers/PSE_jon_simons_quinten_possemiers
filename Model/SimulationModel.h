
#ifndef UNTITLED_SIMULATIONMODEL_H
#define UNTITLED_SIMULATIONMODEL_H


#include <string>
#include "Parser.h"

class SimulationModel {

    /**Section reserved for variables*/
private:

    std::vector<Road *> roads;

    std::vector<Vehicle *> vehicles;

    /**constructor
     *
     * The constructor requires a string with a path leading to the desired xml file to run simulation on
     * */
public:
    SimulationModel();


    /**section reserved for getters and setters!*/

    const std::vector<Vehicle *> &getVehicles() const;

    /**section reserved for public functions*/
public:
    void add_road(Road *road);

    void add_vehicle(Vehicle *vehicle);

    Road *does_road_exist(std::string name);

    void start(const char *xml_path);

};


#endif //UNTITLED_SIMULATIONMODEL_H
