

//============================================================================
// Name        : TicTactToeInputTest.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

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
    ASSERT_TRUE(DirectoryExists("Inputtestfiles"));

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("testInput/zzzInput.xml");
    myfile << "root<<" << endl
           << "\t<BAAN> " << endl
           << "\t<naam>E19</naam>" << endl
           << "\t\t<snelheidslimiet>100</snelheidslimiet>" << endl
           << "\t\t<lengte>1000</lengte>" << endl
           << "\t</BAAN>" << endl
           << "\t<VOERTUIG> " << endl
           << "\t < type >AUTO</type >" << endl
           << "\t\t<nummerplaat>ABC100</nummerplaat>" << endl
           << "\t\t<baan>E19</baan>" << endl
           << "\t\t<positie>100</positie>" << endl
           << "\t\t<snelheid>80</snelheid>" << endl
           << "\t</VOERTUIG>" << endl
           << "</root>" << endl;
    myfile.close();
    myfile.open("testInput/zzzError.txt");
    importResult = Parser::initialiseRoadsAndVehicles(&model, "testInput/zzzInput.xml", myfile);
    myfile.close();
    EXPECT_TRUE(importResult == Success);

    model.automaticSimulation();
    EXPECT_EQ(0, model.getVehicles().size());
}

TEST_F(InputTests, InputLegalGames) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalGame" + to_string(fileCounter) + ".xml";

    while (FileExists(fileName)) {
        myfile.open("testInput/zzzError.txt");
        importResult = TicTacToeImporter::importTicTacToeGame(fileName.c_str(), myfile, ttt_);
        myfile.close();
        EXPECT_TRUE(importResult == Success);
        EXPECT_TRUE(FileIsEmpty("testInput/zzzError.txt"));

        fileCounter = fileCounter + 1;
        fileName = "testInput/legalGame" + to_string(fileCounter) + ".xml";
    };

    EXPECT_TRUE(fileCounter == 12);
}

TEST_F(InputTests, InputXMLSyntaxErrors) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/xmlsyntaxerror" + to_string(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists(fileName)) {
        myfile.open("testInput/zzzError.txt");
        importResult = TicTacToeImporter::importTicTacToeGame(fileName.c_str(), myfile, ttt_);
        myfile.close();
        EXPECT_TRUE(importResult == ImportAborted);
        errorfileName = "testInput/xmlsyntaxerror" + to_string(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("testInput/zzzError.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "testInput/xmlsyntaxerror" + to_string(fileCounter) + ".xml";
    };

    EXPECT_TRUE(fileCounter == 5);
}

TEST_F(InputTests, InputIllegalGames) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/illegalGame" + to_string(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists(fileName)) {
        myfile.open("testInput/zzzError.txt");
        importResult = TicTacToeImporter::importTicTacToeGame(fileName.c_str(), myfile, ttt_);
        myfile.close();
        EXPECT_TRUE(importResult == PartialImport);
        errorfileName = "testInput/illegalError" + to_string(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("testInput/zzzError.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "testInput/illegalGame" + to_string(fileCounter) + ".xml";
    };

    EXPECT_TRUE(fileCounter == 6);
}