
#ifndef UNTITLED_PARSINGEXC_H
#define UNTITLED_PARSINGEXC_H

#include <iostream>
#include <stdexcept>



enum ParsingErr {
    duplicate_plate,road_dupe_name, xml_empty_tag, xml_expected_tag, road_length_null, road_speed_limit_null,
    vehicle_illegal_position, vehicle_collision_error, vehicle_speed_error, non_existing_road,file_root,file_opening_error,dumb
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
        case file_opening_error:        return "File error: could not open file please check the directory!";
        case file_root:                 return "File error: file does not contain a root tag, please check file syntax!";
        default:
        {
            static std::string out = "UNIDENTIFIED ERROR: error id: ";
            out.append(std::to_string(error + 1));
            return out.c_str();
        }

        }

}


class ParsingExc : public std::invalid_argument {
public:
    explicit ParsingExc(const ParsingErr &err);

};

#endif //UNTITLED_PARSINGEXC_H
