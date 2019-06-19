
#include <iostream>
#include "SimulationModel.h"
#include "Exceptions.h"
#include "StatisticsSimulation.h"

const std::string fileName = "test4";

void initSimulation();

int main() {
    initSimulation();
    return 0;
}

void initSimulation() {
    /**
     * Function to initialise the engine handling the simulation
     * */
    try {
        std::string location = "../MainTests/" + fileName + ".xml";
        SimulationModel simulation = SimulationModel();
        Parser p = Parser();
        p.initialiseRoadsAndVehicles(&simulation, location.c_str(), std::cout);
        StatisticsSimulation stat =  StatisticsSimulation(&simulation);
        stat.run();
        stat.toFile("test4Correction");

    } catch (FatalException &e) {
        std::cerr << e.what()<< std::endl;
        exit(e.getExitCode());

    }
};