#include "ParsingExc.h"




int ParsingExc::get_exit_code() {
    return exit_code;
}

static const char *ToStr(const ParsingErr &error) {
    switch (error) {
        case duplicate_plate:           return "Vehicle error: license plate must be unique!";
        case xml_empty_tag:             return "XML error: empty tag!";
        case road_dupe_name:            return "Road error: road must have a unique name!";
        case xml_expected_tag:          return "XML error: received a tag but expected another tag!";
        case road_length_null:          return "Road error: road must have a length of at least 1!";
        case road_speed_limit_null:     return "Road error: speed limit must be at least 1!";
        case vehicle_collision_error:   return "Vehicle error: vehicle collides with another vehicle!";
        case vehicle_illegal_position:  return "Vehicle error: illegal position!";
        case vehicle_speed_error:       return "Vehicle error: speed exceeds the roads limit!";
        case non_existing_road:         return "Road error: road does not exist!";
        case file_opening_error:        return "File error: could not open file please check the directory!";
        case file_root:                 return "File error: file does not contain a root tag, please check file syntax!";
        case road_non_ex_connection_to: return "Road error: road to connect to does not exist!";
        case road_non_ex_connection_from:return"Road error: cannot start a connection from a not existing road!";
        case road_self_connection:      return "Road error: road cannot have a connection to itself!";
        case vehicle_speed_limit:       return "Vehicle error: vehicle is over speed limit!";
        default:
        {
            return "UNIDENTIFIED ERROR";
        }

    }

}

ParsingExc::ParsingExc(const ParsingErr &err) : invalid_argument(ToStr(err)) {
    exit_code = err;
}

FatalException::FatalException(const ParsingErr &err) : invalid_argument(ToStr(err)) {
    exit_code = err;
}


int FatalException::get_exit_code() {
    return exit_code;
}