//
// Created by Quinten on 3/10/2019.
//

#include "ParsingExc.h"

ParsingExc::ParsingExc(const ParsingErr &err) : invalid_argument(ToStr(err)) {}

