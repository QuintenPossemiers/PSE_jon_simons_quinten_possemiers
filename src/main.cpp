
#include <iostream>
#include "SimulationModel.h"
#include "Exceptions.h"

const std::string fileName = "test";

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
        std::cout << simulation;
        simulation.printToFile();


    } catch (FatalException &e) {
        std::cerr << e.what() << std::endl;
        //exit(e.getExitCode());

    }
};