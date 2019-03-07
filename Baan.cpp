//
// Created by student on 07.03.19.
//

#include "Baan.h"

Baan::Baan(const string &naam, int snelheidslimiet, int lengte, const vector<Baan *> &verbinding) : naam(naam),
                                                                                                    snelheidslimiet(
                                                                                                            snelheidslimiet),
                                                                                                    lengte(lengte),
                                                                                                    verbinding(
                                                                                                            verbinding) {}

Baan::Baan(const string &naam, int snelheidslimiet, int lengte) : naam(naam), snelheidslimiet(snelheidslimiet),
                                                                  lengte(lengte) {}

const string &Baan::getNaam() const {
    return naam;
}

int Baan::getSnelheidslimiet() const {
    return snelheidslimiet;
}

int Baan::getLengte() const {
    return lengte;
}

const vector<Baan *> &Baan::getVerbinding() const {
    return verbinding;
}
