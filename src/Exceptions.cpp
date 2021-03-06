#include "Exceptions.h"


static const char *exceptionToStr(const EExceptionText &error) {
    switch (error) {
        case duplicate_plate:               return "Vehicle error: license plate must be unique!";
        case xml_empty_tag:                 return "XML error: empty tag!";
        case road_dupe_name:                return "Road error: road must have a unique fName!";
        case xml_expected_tag:              return "XML error: received a tag but expected another tag!";
        case road_length_null:              return "Road error: road must have a fLength of at least 1!";
        case road_speed_limit_null:         return "Road error: fSpeed limit must be at least 1!";
        case vehicle_collision_error:       return "Vehicle error: vehicle collides with another vehicle!";
        case vehicle_illegal_position:      return "Vehicle error: illegal fPosition!";
        case vehicle_speed_error:           return "Vehicle error: fSpeed exceeds the fRoads limit!";
        case non_existing_road:             return "Road error: road does not exist!";
        case file_opening_error:            return "File error: could not open file please check the directory!";
        case file_root:                     return "File error: file does not contain a root tag, please check file syntax!";
        case road_non_ex_connection_to:     return "Road error: road to connect to does not exist!";
        case road_non_ex_connection_from:   return "Road error: cannot start a connection from a not existing road!";
        case road_self_connection:          return "Road error: road cannot have a connection to itself!";
        case vehicle_speed_limit:           return "Vehicle error: vehicle is over fSpeed limit!";
        case road_fatalException_position_exceeds_limit:   return "Road error: position exeeds the roads length!";
        default: {
            return "UNIDENTIFIED ERROR";
        }

    }

}

NonFatalException::NonFatalException(const EExceptionText &err) : VBaseException(err) {
    fExitCode = err;
}

FatalException::FatalException(const EExceptionText &err) : VBaseException(err) {
    fExitCode = err;
}

FatalException::FatalException(const std::string &msg) : VBaseException(msg, 220) {
    fExitCode = 220;
}


int VBaseException::getExitCode() {
    return fExitCode;
}

VBaseException::VBaseException(const EExceptionText &err) : std::invalid_argument(exceptionToStr(err)), fExitCode(err) {
}

VBaseException::VBaseException(const std::string &msg, int exitCode) : invalid_argument(msg), fExitCode(exitCode) {

}
