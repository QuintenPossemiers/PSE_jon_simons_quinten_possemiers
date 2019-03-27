
#ifndef UNTITLED_PARSINGEXC_H
#define UNTITLED_PARSINGEXC_H

#include <iostream>
#include <stdexcept>



enum EExceptionText {
    duplicate_plate,road_dupe_name, xml_empty_tag, xml_expected_tag, road_length_null, road_speed_limit_null,
    vehicle_illegal_position, vehicle_collision_error, vehicle_speed_error, non_existing_road,file_root,
    file_opening_error, road_non_ex_connection_to, road_non_ex_connection_from, road_self_connection,vehicle_speed_limit
};




class NonFatalException : public std::invalid_argument {

private:
    int fExitCode;
public:
    explicit NonFatalException(const EExceptionText &err);

    int getExitCode();

};

class FatalException : public std::invalid_argument {

private:
    int fExitCode;
public:
    explicit FatalException(const EExceptionText &err);

    int getExitCode();

};

#endif //UNTITLED_PARSINGEXC_H
