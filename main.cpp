
#include <stdio.h>
#include <iostream>
#include "Model/SimulationModel.h"

#include "Model/Exeptions/AllExceptions.h"

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
        std::string location = "../XML_Files/" + file_name + ".xml";
        SimulationModel simulation = SimulationModel();
        simulation.start(location.c_str());
        std::cout << simulation;
        simulation.getVehicles()[0]->set_new_position();


    } catch (ParsingExc &e) {
        std::cerr << e.what() << std::endl;
        exit(e.get_exit_code());
    }
};