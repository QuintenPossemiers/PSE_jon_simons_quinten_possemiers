
#include <iostream>
#include "SimulationModel.h"
#include "Exceptions.h"
#include "StatisticsSimulation.h"

const std::string fileName = "test123";

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
        std::string location = "../XML_Files/" + fileName + ".xml";
        SimulationModel simulation = SimulationModel();
        simulation.start(location.c_str());
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