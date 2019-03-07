cmake_minimum_required(VERSION 3.12)
project(untitled)
set(CMAKE_CXX_STANDARD 14)


add_executable(untitled tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Baan.cpp Baan.h Voertuig.cpp Voertuig.h parser.cpp)