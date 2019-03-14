cmake_minimum_required(VERSION 3.12)
project(untitled)
set(CMAKE_CXX_STANDARD 14)


add_executable(untitled TinyXml/tinystr.cpp TinyXml/tinyxml.cpp TinyXml/tinyxmlerror.cpp TinyXml/tinyxmlparser.cpp   main.cpp Model/SimulationModel.cpp Model/SimulationModel.h Model/Road.cpp Model/Road.h Model/Vehicle.cpp Model/Vehicle.h Model/Parser.cpp Model/Parser.h Model/Exeptions/ParsingExc.cpp Model/Exeptions/ParsingExc.h Model/Exeptions/AllExceptions.h Model/VehicleTypes.h)