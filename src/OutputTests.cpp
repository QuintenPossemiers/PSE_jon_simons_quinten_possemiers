#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "SimulationModel.h"
#include "StatisticsSimulation.h"
#include "Utils.h"

class OutputTest: public ::testing::Test {
protected:
    friend class TicTacToe;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    SimulationModel model;

};


TEST_F(OutputTest, OutputHappyDay) {
    //if directory doesn't exist then no need in proceeding with the test



    ofstream myfile;
    myfile.open("../MainTests/test1Errors.xml");
    Parser p = Parser();
    p.initialiseRoadsAndVehicles(&model,"../MainTests/test1.xml",myfile );
    StatisticsSimulation s = StatisticsSimulation(&model);
    s.run();
    s.toFile("../MainTests/test1Out.xml");
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../MainTests/test1Out.xml", "../MainTests/test1Correction.xml"));
}


