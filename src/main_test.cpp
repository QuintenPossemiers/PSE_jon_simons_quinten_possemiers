#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "SimulationModel.h"
#include "Road.h"
#include "Vehicle.h"
#include "Exeptions/ParsingExc.h"

using namespace std;


class SimulationModelTest : public ::testing::Test {
protected:
    friend class SimulationModel;


    SimulationModel simulationModel_;
    Road *road_1_;
    Road *road_2_;
    Vehicle *car_1_;
    Vehicle *car_2_;

    virtual void SetUp() {
        road_1_ = new Road("A12", 120, 5000);
        road_2_ = new Road("E43", 100, 5010);
        car_1_ = new Vehicle(50, 100, "abcdefg", road_1_, new VehicleType("AUTO"));
        car_2_ = new Vehicle(50, 250, "1234567", road_1_, new VehicleType("AUTO"));
        simulationModel_.add_road(road_1_);
        simulationModel_.add_road(road_2_);
        simulationModel_.add_vehicle(car_1_);
        simulationModel_.add_vehicle(car_2_);
    }


    virtual void TearDown() {

    }


};

TEST_F(SimulationModelTest, InputFileTest) {
    Parser parser = Parser("ikhoopdatditnietbestaat.xml");
    EXPECT_THROW(parser.initialise_roads_and_vehicles(&simulationModel_), exception);
}

TEST_F(SimulationModelTest, InconsistenteVerkeersSituatie) {
    Road *wrong = new Road("/0", 9001, 1);
    Vehicle *wrong_2 = new Vehicle(50, 0, "abcdefh", wrong, new VehicleType("AUTO"));
    EXPECT_THROW(simulationModel_.add_vehicle(wrong_2), FatalException);
    EXPECT_THROW(Vehicle(0, 6000, "nummerplaat", road_1_, new VehicleType("AUTO")), FatalException);
    EXPECT_THROW(simulationModel_.add_vehicle(new Vehicle(50, 100, "abcdefp", road_1_, new VehicleType("AUTO"))),
                 FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.add_vehicle(
            new Vehicle(50, 4500, "abcdefp", road_1_, new VehicleType("AUTO"))));
    EXPECT_THROW(simulationModel_.addConnection(road_1_, wrong),FatalException);
    //EXPECT_THROW(simulationModel_.add_vehicle(wrong_2),FatalException);
    EXPECT_NO_FATAL_FAILURE(simulationModel_.addConnection(road_1_,road_2_));
}

TEST_F(SimulationModelTest, OutputTest){
    std::stringstream received_road;
    received_road << *road_1_;
    std::string  output_test_road = "Baan: A12\n --> snelheidslimiet  : 120\n --> lengte           : 5000\n";
    std::string output_test_road_2= received_road.str();

    std::stringstream received_vehicle;
    received_vehicle << *car_1_;
    std::string  output_test_vehicle = "Voertuig: AUTO (abcdefg)\n --> baan    : A12\n --> positie : 100\n --> snelheid: 50\n";
    std::string output_test_vehicle_2= received_vehicle.str();

    EXPECT_EQ(output_test_road,output_test_road_2 );
    EXPECT_EQ(output_test_vehicle, output_test_vehicle_2);
}

//
//TEST_F(SimulationModelTest, ProperlyInitialised) {
//    EXPECT_TRUE(simulationModel_.properlyInitialized());
//    EXPECT_TRUE(car_1_->properlyInitialized());
//    EXPECT_TRUE(car_2_->properlyInitialized());
//    EXPECT_TRUE(car_1_->properlyInitialized());
//    EXPECT_TRUE(car_1_->properlyInitialized());//todo
//
//}
//
//TEST_F(SimulationModelTest, InvalidVehicle) {
//
//    EXPECT_THROW(Vehicle(150, 1200, "", road_1_, new VehicleType("AUTO")), exception);
//    EXPECT_THROW(Vehicle(25, 5001, "", road_1_, new VehicleType("AUTO")), exception);
//}
//
//TEST_F(SimulationModelTest, InvalidRoad) {
//    simulationModel_.add_road(road_1_);
//
//
//
//    EXPECT_THROW(simulationModel_.add_road(road_1_), ParsingExc);
//}

//
//
//
//
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



/**
 * Parser constructor
 * */