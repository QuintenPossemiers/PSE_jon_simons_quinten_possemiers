//
// Created by student on 07.03.19.
//

#include "Voertuig.h"

Voertuig::Voertuig(const string &type, const string &nummerplaat, Baan *baan, int positie, int snelheid) : type(type),
                                                                                                           nummerplaat(
                                                                                                                   nummerplaat),
                                                                                                           baan(baan),
                                                                                                           positie(positie),
                                                                                                           snelheid(
                                                                                                                   snelheid) {}
