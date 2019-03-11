//
// Created by Quinten on 3/10/2019.
//

#include "ParsingExc.h"

ParsingExc::ParsingExc(const ParsingErr &err) : invalid_argument(ToStr(err)) {
    exit_code = err;
}

int ParsingExc::get_exit_code() {
    return exit_code;
}

