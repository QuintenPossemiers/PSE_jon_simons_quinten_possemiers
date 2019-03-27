
#ifndef UNTITLED_PARSINGEXC_H
#define UNTITLED_PARSINGEXC_H

#include <iostream>
#include <stdexcept>
#include "DesignByContract.h"


enum EExceptionText {
    duplicate_plate,
    road_dupe_name,
    xml_empty_tag,
    xml_expected_tag,
    road_length_null,
    road_speed_limit_null,
    vehicle_illegal_position,
    vehicle_collision_error,
    vehicle_speed_error,
    non_existing_road,
    file_root,
    file_opening_error,
    road_non_ex_connection_to,
    road_non_ex_connection_from,
    road_self_connection,
    vehicle_speed_limit
};


class VBaseException : public std::invalid_argument {
protected:
    int fExitCode;
public:
    explicit VBaseException(const EExceptionText &err);

    virtual int getExitCode();
    /*!
     * Deze functie zal de exit code terug geven aan de hand van de enum EEXcptionText
     * @return int code*/


};

class NonFatalException : public VBaseException {
public:
    explicit NonFatalException(const EExceptionText &err);
    /*!
     * basis constructor: maakt een NonFatalException aan
     * @param err requires an EExceptionText die de text van de exception zal initializeren.
     * */
};


class FatalException : public VBaseException {
public:
    explicit FatalException(const EExceptionText &err);
    /*!
     * basis constructor: maakt een NonFatalException aan
     * @param err requires an EExceptionText die de text van de exception zal initializeren.
     * */
};

#endif //UNTITLED_PARSINGEXC_H
