cmake_minimum_required(VERSION 3.12)
project(untitled)
set(CMAKE_CXX_STANDARD 98)


add_executable(untitled TinyXml/tinystr.cpp TinyXml/tinyxml.cpp TinyXml/tinyxmlerror.cpp TinyXml/tinyxmlparser.cpp   main.cpp src/SimulationModel.cpp src/SimulationModel.h src/Road.cpp src/Road.h src/Vehicle.cpp src/Vehicle.h src/Parser.cpp src/Parser.h src/Exeptions/ParsingExc.cpp src/Exeptions/ParsingExc.h src/Exeptions/AllExceptions.h main_test.cpp)