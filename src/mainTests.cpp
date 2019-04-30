#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "SimulationModel.h"
#include "Road.h"
#include "Vehicle.h"
#include "Exceptions.h"

using namespace std;


class SimulationModelTest : public ::testing::Test {
protected:
    friend class SimulationModel;


    SimulationModel simulationModel_;
    Road *road1;
    Road *road;
    Vehicle *car1;
    Vehicle *car2;
    Vehicle *car3;

    virtual void SetUp() {
        road1 = new Road("A12", 120, 5000);
        road = new Road("E43", 100, 4500);
        car1 = new Car(50, 100, "abcdefg", road1);
        car2 = new Car(100, 4490, "1234567", road);
        car3 = new Car(120, 4990, "SPEEDY", road1);

        simulationModel_.addRoad(road1);
        simulationModel_.addRoad(road);
        simulationModel_.addVehicle(car1);
        simulationModel_.addVehicle(car2);
        simulationModel_.addVehicle(car3);
        simulationModel_.addConnection(road, road1);

    }


    virtual void TearDown() {

    }

};

TEST_F(SimulationModelTest, ProperlyInitialised) {
    EXPECT_TRUE(simulationModel_.properlyInitialized());
    EXPECT_TRUE(car1->properlyInitialised());
    EXPECT_TRUE(car2->properlyInitialised());
    EXPECT_TRUE(road1->properlyInitialized());
    EXPECT_TRUE(road->properlyInitialized());
    Parser p = Parser("../XML_Files/test.xml");
    EXPECT_TRUE(p.properlyInitialized());
}

TEST_F(SimulationModelTest, RoadVerkeersTekens) {
    Road road = Road("A12", 120, 5000);

    EXPECT_EQ((unsigned int )120, road.getSpeedLimit(0));
    //EXPECT_THROW(road.getSpeedLimit(50000),FatalException); // todo fix tests
    EXPECT_EQ((unsigned int) 120, road.getSpeedLimit(0));


    EXPECT_EQ(-1, road.getNextBusStop(1200));

    EXPECT_NO_FATAL_FAILURE(road.addBusStop(10));
    EXPECT_NO_FATAL_FAILURE(road.addBusStop(1050));
    EXPECT_NO_FATAL_FAILURE(road.addBusStop(150));

    EXPECT_EQ(-1, road.getNextBusStop(1200));
    EXPECT_EQ(10, road.getNextBusStop(0));
    EXPECT_EQ(150, road.getNextBusStop(120));

    road.addZone(4000, 75);
    road.addZone(2000, 50);
    road.addZone(175, 90);

    EXPECT_EQ((unsigned int) 75, road.getSpeedLimit(4001));
    EXPECT_EQ((unsigned int) 120, road.getSpeedLimit(100));
    EXPECT_EQ((unsigned int) 90, road.getSpeedLimit(180));
    EXPECT_EQ((unsigned int) 50, road.getSpeedLimit(2500));


    EXPECT_DEATH(road.addTrafficLight((unsigned int)5020), "positie moet kleiner zijn dan de lengte van de baan");
    EXPECT_DEATH(road.addZone(5020, 50), "positie moet kleiner zijn dan de lengte van de baan");
    EXPECT_DEATH(road.addZone(10, 250),  "snelheidslimiet van de baan wordt overschreden");

    TrafficLight x = TrafficLight(0);
    EXPECT_TRUE(x.properlyInitialised());
    EXPECT_EQ("red", x.getColor());
    for (int i = 0; i < 30; ++i)
        x.clockCycle();
    EXPECT_EQ("green", x.getColor());
    for (int i = 0; i < 30; ++i)
        x.clockCycle();
    EXPECT_EQ("orange", x.getColor());
    for (int i = 0; i < 5; ++i)
        x.clockCycle();
    EXPECT_EQ("red", x.getColor());

    //todo tests on functionaliteit niet auto


    //EXPECT_THROW(road.getNextBusStop(5001),FatalException);
    //EXPECT_DEATH_IF_SUPPORTED(road.addBusStop(5001), "positie moet kleiner zijn dan de lengte van de baan");

}




TEST_F(SimulationModelTest, InputFileTest) {
    Parser parser = Parser("ikhoopdatditnietbestaat.xml");
    EXPECT_THROW(parser.initialiseRoadsAndVehicles(&simulationModel_), exception);

    std::string fileLocation = "../XML_Files/";
    std::string loc1 = fileLocation + "testWrongTags.xml";
    std::string loc2 = fileLocation + "testAmountOfCarsAndRoads.xml";
    Parser p1 = Parser(loc1.c_str());
    EXPECT_THROW(p1.initialiseRoadsAndVehicles(&simulationModel_),FatalException);
    SimulationModel * s1 = new SimulationModel();
    Parser p2 = Parser(loc2.c_str());
    p2.initialiseRoadsAndVehicles(s1);


    EXPECT_EQ((unsigned int)2, s1->getVehicles().size());
    EXPECT_EQ((unsigned int)2, s1->getRoads().size());
}

TEST_F(SimulationModelTest, InconsistenteVerkeersSituatie) {
    Road *wrong = new Road("/0", 9001, 1);
    Vehicle *wrong_2 = new Car(50, 0, "abcdefh", wrong);
    EXPECT_THROW(simulationModel_.addVehicle(wrong_2), FatalException);
    EXPECT_THROW(Car(0, 6000, "nummerplaat", road1), FatalException);
    EXPECT_THROW(simulationModel_.addVehicle(new Car(50, 100, "abcdefp", road1)),
                 FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.addVehicle(
            new Car(50, 4500, "abcdefp", road1)));
    EXPECT_THROW(simulationModel_.addConnection(road1, wrong), FatalException);
    EXPECT_THROW(simulationModel_.addVehicle(wrong_2),FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.addConnection(road1, road));
    EXPECT_THROW(Car(25, 5001, "", road1), FatalException);
    EXPECT_THROW(Car(150, 1200, "", road1), NonFatalException);

}


TEST_F(SimulationModelTest, OutputTest) {
    std::stringstream receivedRoad;
    receivedRoad << *road1;
    std::string outputTestRoad =
            "Baan: A12\n --> snelheidslimiet  : 120\n --> lengte           : 5000\n";
    std::string outputTestRoad2 = receivedRoad.str();

    std::stringstream receivedVehicle;
    receivedVehicle << *car1;
    std::string outputTestVehicle =
            "Voertuig: auto (abcdefg)\n --> baan    : A12\n --> positie : 100\n --> snelheid: 50\n";
    std::string outputTestVehicle2 = receivedVehicle.str();

    std::string outputTest2Road =
            "Baan: E43\n --> snelheidslimiet  : 100\n --> lengte           : 4500\n --> verbinding       : A12\n";


    std::stringstream receivedRoad2;
    receivedRoad2 << *road;
    std::string outputTest2Road2 = receivedRoad2.str();


    EXPECT_EQ(outputTestRoad, outputTestRoad2);
    EXPECT_EQ(outputTestVehicle, outputTestVehicle2);
    EXPECT_EQ(outputTest2Road2, outputTest2Road);
}


TEST_F(SimulationModelTest, Movement) {
    EXPECT_EQ(road1, car1->getFCurrentRoad());
    EXPECT_EQ(road, car2->getFCurrentRoad());
    EXPECT_EQ((unsigned long) 3, simulationModel_.getVehicles().size());
    simulationModel_.tick();
    EXPECT_EQ(road1, car2->getFCurrentRoad());
    EXPECT_EQ(road1, car1->getFCurrentRoad());
    EXPECT_EQ((const unsigned int) 102, car2->getFSpeed());
    EXPECT_EQ((const unsigned int) 52, car1->getFSpeed());
    EXPECT_EQ((const unsigned int) 0, car2->getFPosition());
    EXPECT_EQ((const double) 114, car1->getFPosition());
    EXPECT_EQ((unsigned long) 2, simulationModel_.getVehicles().size());

    EXPECT_EQ(road1, car1->getFCurrentRoad());
}

TEST_F(SimulationModelTest, Automatic) {
    EXPECT_EQ(road1, car1->getFCurrentRoad());
    EXPECT_EQ(road, car2->getFCurrentRoad());
    EXPECT_EQ((unsigned long) 3, simulationModel_.getVehicles().size());
    simulationModel_.automaticSimulation();
    EXPECT_EQ((unsigned long) 0, simulationModel_.getVehicles().size());

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



/**
 * Parser constructor
 * */