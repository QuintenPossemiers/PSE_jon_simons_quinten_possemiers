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


// Tests the compare files
TEST_F(OutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("testOutput"));

    ofstream myfile;
    myfile.open("../testOutput/file1.txt");
    myfile.close();
    myfile.open("../testOutput/file2.txt");
    myfile.close();

    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("../testOutput/file2.txt"));


    //compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("testOutput/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file1.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare two equal files
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../testOutput/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("../testOutput/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file2.txt", "../testOutput/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("../testOutput/file1.txt", "testOutput/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../testOutput/nonexisting.txt", "testOutput/file1.txt"));
}


TEST_F(OutputTest, OutputHappyDay) {
    ASSERT_TRUE(DirectoryExists("testOutput"));
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


