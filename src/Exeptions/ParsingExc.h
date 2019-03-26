
#ifndef UNTITLED_PARSINGEXC_H
#define UNTITLED_PARSINGEXC_H

#include <iostream>
#include <stdexcept>



enum ParsingErr {
    duplicate_plate,road_dupe_name, xml_empty_tag, xml_expected_tag, road_length_null, road_speed_limit_null,
    vehicle_illegal_position, vehicle_collision_error, vehicle_speed_error, non_existing_road,file_root,
    file_opening_error, road_non_ex_connection_to, road_non_ex_connection_from, road_self_connection,vehicle_speed_limit
};




class ParsingExc : public std::invalid_argument {

private:
    int exit_code;
public:
    explicit ParsingExc(const ParsingErr &err);

    int get_exit_code();

};

#endif //UNTITLED_PARSINGEXC_H
