//
// Created by student on 07.03.19.
//

#ifndef PSE_VOERTUIG_H
#define PSE_VOERTUIG_H



#include "iostream"
#include <vector>
#include "Baan.h"

using namespace std;

class Voertuig {
    string type;
    string nummerplaat;
    Baan* baan;
    int positie;
    int snelheid;

public:
    Voertuig(const string &type, const string &nummerplaat, Baan *baan, int positie, int snelheid);

};


#endif //PSE_VOERTUIG_H
