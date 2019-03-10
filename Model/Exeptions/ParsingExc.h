//
// Created by Quinten on 3/10/2019.
//

#ifndef UNTITLED_PARSINGEXC_H
#define UNTITLED_PARSINGEXC_H

#include <iostream>
#include <stdexcept>


enum ParsingErr {
    duplicate_plate,road_dupe_name, xml_empty_tag, xml_expected_tag, road_length_null, road_speed_limit_null,
    vehicle_illegal_position, vehicle_collision_error, vehicle_speed_error, non_existing_road
};

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
        default:                        return "UNIDENTIFIED ERROR";
    }
}


class ParsingExc : public std::invalid_argument {
public:
    explicit ParsingExc(const ParsingErr &err);

};

#endif //UNTITLED_PARSINGEXC_H
