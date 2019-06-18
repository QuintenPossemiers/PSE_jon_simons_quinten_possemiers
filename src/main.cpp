
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
        simulation.sort();
        stat.run();
        stat.toFile("tests");
        std::cout << simulation;
        //simulation.automaticSimulation();
        simulation.printToFile();

    } catch (FatalException &e) {
        std::cerr << e.what()<< std::endl;
        exit(e.getExitCode());

    }
};