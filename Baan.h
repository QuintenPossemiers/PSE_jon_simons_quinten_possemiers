//
// Created by student on 07.03.19.
//

#ifndef PSE_BAAN_H
#define PSE_BAAN_H

#include "iostream"
#include <vector>

using namespace std;

class Baan {
private:
    string naam;
    int snelheidslimiet;
    int lengte;
    vector<Baan *> verbinding;
public:
    Baan(const string &naam, int snelheidslimiet, int lengte, const vector<Baan *> &verbinding);

    Baan(const string &naam, int snelheidslimiet, int lengte);

    const string &getNaam() const;

    int getSnelheidslimiet() const;

    int getLengte() const;

    const vector<Baan *> &getVerbinding() const;

};


#endif //PSE_BAAN_H
