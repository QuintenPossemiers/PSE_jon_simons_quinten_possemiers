

#ifndef UNTITLED_SIMULATIONMODEL_H
#define UNTITLED_SIMULATIONMODEL_H

#include <string>
#include <ostream>
#include "Parser.h"
#include "DesignByContract.h"


class SimulationModel {

private:

    SimulationModel *_initCheck;

    std::vector<Road *> fRoads;

    std::vector<Vehicle *> fVehicles;

public:
    SimulationModel();
    //ENSURE(properlyInitialized(),"simulatie model is niet goed geinitialiseerd")

    std::vector<Vehicle *> &getVehicles();
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");


    std::vector<Road *> &getRoads();
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");

    void addRoad(Road *road);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    //REQUIRE(road!= NULL,"geen geldige baan");
    //ENSURE(fRoads.size()==i,"baan niet toegevoegd")


    bool properlyInitialized();

    void addVehicle(Vehicle *vehicle);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    //REQUIRE(vehicle!= NULL,"geen geldig voertuig");
    //ENSURE(fVehicles.size()==i,"voertuig niet toegevoegd")


    Road *doesRoadExist(std::string name);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");


    void start(const char *xml_path);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");


    void tick(unsigned int time = 1);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");


    void checkCollision(Vehicle *vehicle);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    //REQUIRE(vehicle!= NULL,"geen geldig voertuig");


    void addConnection(Road *from, Road *to);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    //REQUIRE(from!= NULL,"geen geldige baan waarvan je vertrekt");
    //REQUIRE(to!= NULL,"geen geldige baan waar je naartoe gaat");
    //ENSURE(from->getConnections().size()==i,"connectie niet toegevoegd");


    void automaticSimulation();
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");
    //ENSURE(fVehicles.empty(),"simulatie mislukt");


    friend std::ostream &operator<<(std::ostream &os, SimulationModel &model);
    //REQUIRE(properlyInitialized(),"simulatie model niet geinitialiseerd");


private:
    std::vector<Vehicle *> get_vehicle_on_road(Road *road);


};

#endif //UNTITLED_SIMULATIONMODEL_H
