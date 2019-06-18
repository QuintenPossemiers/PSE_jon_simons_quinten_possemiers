

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


class InputTests: public ::testing::Test {
protected:
    friend class SimulationModel;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    TicTacToe ttt_;
};

/**
Tests InputHappyDay
*/
TEST_F(InputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("Inputtestfiles"));

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("testInput/zzzInput.xml");
    myfile << "<?xml version=\"1.0\" ?>" << endl
           << "<TicTacToe>" << endl
           << "\t<MOVES_O>a1c1b2a3c3</MOVES_O>" << endl
           << "\t<MOVES_X>b1a2c2b3</MOVES_X>" << endl
           << "</TicTacToe>" << endl;
    myfile.close();
    myfile.open("testInput/zzzError.txt");
    importResult = TicTacToeImporter::importTicTacToeGame("testInput/zzzInput.xml", myfile, ttt_);
    myfile.close();
    EXPECT_TRUE(importResult == Success);

    while (ttt_.notDone()) {
        ttt_.doMove();
    };

    char col, row;
    bool markIsX = false; // start with 'O'
    // The diagonal is recognised as a winner. Sow we stop after verifying first two rows
    for (row = minRow; row < maxRow; row++)
        for (col = minCol; col <= maxCol; col++) {
            if (markIsX)
                EXPECT_EQ('X', ttt_.getMark(col, row));
            else
                EXPECT_EQ('O', ttt_.getMark(col, row));
            markIsX = not markIsX;
        };
    EXPECT_FALSE(ttt_.notDone());
    EXPECT_EQ(7, ttt_.nrOfMoves());
    EXPECT_EQ('O', ttt_.getWinner());

}

TEST_F(TicTactToeInputTest, InputLegalGames) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/legalGame" + to_string(fileCounter) + ".xml";

    while (FileExists (fileName)) {
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

TEST_F(TicTactToeInputTest, InputXMLSyntaxErrors) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/xmlsyntaxerror" + to_string(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
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

TEST_F(TicTactToeInputTest, InputIllegalGames) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "testInput/illegalGame" + to_string(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
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