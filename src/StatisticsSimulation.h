//
// Created by quinten on 17.06.19.
//

#ifndef UNTITLED_STATISTICSSIMULATION_H
#define UNTITLED_STATISTICSSIMULATION_H

#include "SimulationModel.h"
#include "DataStats.h"
#include <map>

class StatisticsSimulation {
    SimulationModel* fSimulation;
    std::map<std::string, DataStats> fData;

public:
    StatisticsSimulation(SimulationModel *simulation);

    void toFile(const char* name);

    void run();
};


#endif //UNTITLED_STATISTICSSIMULATION_H
