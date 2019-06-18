//
// Created by quinten on 17.06.19.
//

#include "SimulationModel.h"
#include "StatisticsSimulation.h"


StatisticsSimulation::StatisticsSimulation(SimulationModel *simulation):fSimulation(simulation) {

}

void StatisticsSimulation::run() {
    for (unsigned int i = 0; i < fSimulation->getVehicles().size(); ++i) {
        std::string lp = fSimulation->getVehicles()[i]->getKLicencePlate();
        fData.insert(std::pair<std::string, DataStats>(lp, DataStats(lp)));
    }
    while (!fSimulation->getVehicles().empty()) {
        fSimulation->tick();
        for (unsigned int i = 0; i < fSimulation->getVehicles().size(); ++i) {
            std::string lp = fSimulation->getVehicles()[i]->getKLicencePlate();
            fData[lp].add(fSimulation->getVehicles()[i]->getFSpeed());
        }
    }
    std::map<std::string, DataStats>::iterator it;
    for (it = fData.begin(); it != fData.end(); it++)
    {
        std::cout << it->second;
    }
}
