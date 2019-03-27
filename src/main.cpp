
#include <stdio.h>
#include <iostream>
#include "SimulationModel.h"

#include "Exeptions/Exceptions.h"

static std::string file_name = "test";

void init_simulation();

int main() {
    init_simulation();
    return 0;
}

void init_simulation() {
    /**
     * Function to initialise the engine handling the simulation
     * */
    try {
        std::string location = "../XML_Files/" + file_name + ".xml";
        SimulationModel simulation = SimulationModel();
        simulation.start(location.c_str());
        std::cout << simulation;


    } catch (FatalException &e) {
        std::cerr << e.what() << std::endl;
        //exit(e.getExitCode());

    }
};