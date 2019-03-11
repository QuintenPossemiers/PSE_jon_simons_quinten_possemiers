
#include <stdio.h>
#include <iostream>
#include "Model/SimulationModel.h"

const std::string file_name = "test";

SimulationModel *init_simulation();

int main() {
    init_simulation();
    return 0;
}

SimulationModel *init_simulation() {
    /**
     * Function to initialise the engine handling the simulation
     * */
    try {
        std::string location = "../XML_Files/" + file_name + ".xmll";
        SimulationModel simulation = SimulationModel();
        simulation.start(location.c_str());

    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
};