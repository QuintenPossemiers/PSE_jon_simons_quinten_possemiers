cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES src/main.cpp src/Parser.cpp src/Vehicle.cpp
        src/Road.cpp src/SimulationModel.cpp src/Exceptions.cpp TinyXml/tinystr.cpp TinyXml/tinyxml.cpp TinyXml/tinyxmlerror.cpp TinyXml/tinyxmlparser.cpp src/DesignByContract.h src/TrafficLight.cpp src/TrafficLight.h src/DataStats.cpp src/DataStats.h src/StatisticsSimulation.cpp src/StatisticsSimulation.h )

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES src/mainTests.cpp src/Parser.cpp src/Vehicle.cpp
        src/Road.cpp src/SimulationModel.cpp src/Exceptions.cpp TinyXml/tinystr.cpp TinyXml/tinyxml.cpp TinyXml/tinyxmlerror.cpp TinyXml/tinyxmlparser.cpp src/TrafficLight.cpp src/TrafficLight.h src/InputTests.cpp src/Utils.cpp src/Utils.h src/OutputTests.cpp src/mainTests.cpp)


# Create RELEASE target
add_executable(pse ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(pse_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(pse_debug gtest)