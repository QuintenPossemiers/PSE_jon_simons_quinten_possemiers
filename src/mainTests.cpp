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
        car1 = new Vehicle(50, 100, "abcdefg", road1, new VehicleType("AUTO"));
        car2 = new Vehicle(100, 4490, "1234567", road, new VehicleType("AUTO"));
        car3 = new Vehicle(120, 4990, "SPEEDY", road1, new VehicleType("AUTO"));

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
    EXPECT_TRUE(car1->properlyInitialized());
    EXPECT_TRUE(car2->properlyInitialized());
    EXPECT_TRUE(road1->properlyInitialized());
    EXPECT_TRUE(road->properlyInitialized());
}

TEST_F(SimulationModelTest, InputFileTest) {
    Parser parser = Parser("ikhoopdatditnietbestaat.xml");
    EXPECT_THROW(parser.initialiseRoadsAndVehicles(&simulationModel_), exception);
}

TEST_F(SimulationModelTest, InconsistenteVerkeersSituatie) {
    Road *wrong = new Road("/0", 9001, 1);
    Vehicle *wrong_2 = new Vehicle(50, 0, "abcdefh", wrong, new VehicleType("AUTO"));
    EXPECT_THROW(simulationModel_.addVehicle(wrong_2), FatalException);
    EXPECT_THROW(Vehicle(0, 6000, "nummerplaat", road1, new VehicleType("AUTO")), FatalException);
    EXPECT_THROW(simulationModel_.addVehicle(new Vehicle(50, 100, "abcdefp", road1, new VehicleType("AUTO"))),
                 FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.addVehicle(
            new Vehicle(50, 4500, "abcdefp", road1, new VehicleType("AUTO"))));
    EXPECT_THROW(simulationModel_.addConnection(road1, wrong), FatalException);
    //EXPECT_THROW(simulationModel_.addVehicle(wrong_2),FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.addConnection(road1, road));
    EXPECT_THROW(Vehicle(25, 5001, "", road1, new VehicleType("AUTO")), FatalException);
    EXPECT_THROW(Vehicle(150, 1200, "", road1, new VehicleType("AUTO")), NonFatalException);

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
            "Voertuig: AUTO (abcdefg)\n --> baan    : A12\n --> positie : 100\n --> snelheid: 50\n";
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
    EXPECT_EQ(road1, car1->getCurrentRoad());
    EXPECT_EQ(road, car2->getCurrentRoad());
    EXPECT_EQ((unsigned long) 3, simulationModel_.getVehicles().size());
    simulationModel_.tick();
    EXPECT_EQ(road1, car2->getCurrentRoad());
    EXPECT_EQ(road1, car1->getCurrentRoad());
    EXPECT_EQ((const unsigned int) 102, car2->getSpeed());
    EXPECT_EQ((const unsigned int) 52, car1->getSpeed());
    EXPECT_EQ((const unsigned int) 0, car2->getPosition());
    EXPECT_EQ((const double) 114, car1->getPosition());
    EXPECT_EQ((unsigned long) 2, simulationModel_.getVehicles().size());

    EXPECT_EQ(road1, car1->getCurrentRoad());
}

TEST_F(SimulationModelTest, Automatic) {
    EXPECT_EQ(road1, car1->getCurrentRoad());
    EXPECT_EQ(road, car2->getCurrentRoad());
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