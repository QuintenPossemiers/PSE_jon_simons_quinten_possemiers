

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "SimulationModel.h"
#include "Utils.h"


class InputTests : public ::testing::Test {
protected:
    friend class SimulationModel;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    SimulationModel model;
};

/**
Tests InputHappyDay
*/
TEST_F(InputTests, InputHappyDay) {

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("zzzInput.xml");
    myfile << "<root>" << endl
           << "\t<BAAN> " << endl
           << "\t<naam>E19</naam>" << endl
           << "\t\t<snelheidslimiet>100</snelheidslimiet>" << endl
           << "\t\t<lengte>1000</lengte>" << endl
           << "\t</BAAN>" << endl
           << "\t<VOERTUIG> " << endl
           << "\t <type>AUTO</type>" << endl
           << "\t\t<nummerplaat>ABC100</nummerplaat>" << endl
           << "\t\t<baan>E19</baan>" << endl
           << "\t\t<positie>100</positie>" << endl
           << "\t\t<snelheid>80</snelheid>" << endl
           << "\t</VOERTUIG>" << endl
           << "</root>" << endl;
    myfile.close();
    myfile.open("zzzError.txt");
    importResult = Parser::initialiseRoadsAndVehicles(&model, "zzzInput.xml", myfile);
    myfile.close();
    EXPECT_TRUE(importResult == Success);

    model.automaticSimulation();
    EXPECT_EQ((unsigned int)0, model.getVehicles().size());
}

TEST_F(InputTests, InputLegalGames) {

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "../Inputtestfiles/legalInput" + to_string(fileCounter) + ".xml";

    while (FileExists(fileName)) {
        myfile.open("zzzError.txt");
        importResult = Parser::initialiseRoadsAndVehicles(&model, "zzzInput.xml", myfile);
        myfile.close();
        EXPECT_TRUE(importResult == Success);
        EXPECT_TRUE(FileIsEmpty("zzzError.txt"));

        fileCounter++;
        fileName = "../Inputtestfiles/legalInput" + to_string(fileCounter) + ".xml";;
    };

    EXPECT_TRUE(fileCounter == 6);
}


