

#ifndef UNTITLED_SIMULATIONMODEL_H
#define UNTITLED_SIMULATIONMODEL_H

#include <string>
#include <ostream>
#include "Parser.h"


class SimulationModel {

    /**Section reserved for variables*/
private:

    SimulationModel* _initCheck;

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

    const std::vector<Road *> &getRoads() const;

    /**section reserved for public functions*/
public:
    void add_road(Road *road);

    bool properlyInitialized();

    void add_vehicle(Vehicle *vehicle);

    Road *does_road_exist(std::string name);

    void start(const char *xml_path);

    void tick(unsigned int time = 1);

    void checkCollision(Vehicle* vehicle);

    void addConnection(Road* from, Road* to);

    /**section for overloaded operators*/
public:
    friend std::ostream &operator<<(std::ostream &os, const SimulationModel &model);

private:
    std::vector<Vehicle*> get_vehicle_on_road(Road* road);




};

#endif //UNTITLED_SIMULATIONMODEL_H
