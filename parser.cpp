#include <iostream>
#include "tinyxml.h"
#include "Baan.h"
#include "Voertuig.h"
#include <vector>


vector<Baan *> read_baan(vector<TiXmlElement *> input_elements) {
    vector<Baan *> banen;
    for (auto elem  :input_elements) {
        string naam;
        int snelheidslimiet = 0;
        int lengte = 0;
        for (TiXmlElement *attribute = elem->FirstChildElement();
             attribute != nullptr; attribute = attribute->NextSiblingElement()) {
            std::string elemName = attribute->Value();
            if (elemName == "naam")naam = attribute->GetText();
            else if (elemName == "snelheidslimiet")snelheidslimiet = stoi(attribute->GetText());
            else if (elemName == "lengte")lengte = stoi(attribute->GetText());
        }
        //todo exeption handling
        banen.emplace_back(new Baan(naam, snelheidslimiet, lengte));
    }
    return banen;
}

vector<Voertuig *> read_voertuig(vector<TiXmlElement *> input_elements, vector<Baan *> &banen) {
    vector<Voertuig *> voertuigen;
    for (auto elem  :input_elements) {
        string type;
        string nummerplaat;
        string baan;
        int positie = 0;
        int snelheid = 0;
        for (TiXmlElement *attribute = elem->FirstChildElement();
             attribute != nullptr; attribute = attribute->NextSiblingElement()) {
            std::string elemName = attribute->Value();
            if (elemName == "type")type = attribute->GetText();
            else if (elemName == "nummerplaat")nummerplaat = attribute->GetText();
            else if (elemName == "baan")baan = attribute->GetText();
            else if (elemName == "positie")positie = stoi(attribute->GetText());
            else if (elemName == "snelheid")snelheid = stoi(attribute->GetText());
            //todo exeption handling
        }
        Baan *pointer_baan = nullptr;
        for (auto item :banen) {
            if (item->getNaam() == baan) {
                pointer_baan = item;
                break;
            }
        }
        if (pointer_baan != nullptr)
            voertuigen.emplace_back(new Voertuig(type, nummerplaat, pointer_baan, positie, snelheid));
    }
    return voertuigen;
}

int main() {
    vector<Baan *> final_banen;
    vector<Voertuig *> final_voertuigen;

    TiXmlDocument doc;
    if (!doc.LoadFile("../test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    TiXmlElement *root = doc.FirstChildElement();
    if (root == nullptr) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }

    vector<TiXmlElement *> banen;
    vector<TiXmlElement *> voertuigen;

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement()) {


        std::cout << elem->Value() << endl;
        if (elem->FirstChild() != nullptr) {

            std::string elemName = elem->Value();
            if (elemName == "BAAN") {
                banen.push_back(elem);
            } else if (elemName == "VOERTUIG") {
                voertuigen.push_back(elem);
            }
        }
        //todo exeptionhandling
    }

    final_banen = read_baan(banen);
    final_voertuigen = read_voertuig(voertuigen, final_banen);

    cout << final_banen[0]->getNaam();
    doc.Clear();

    return 0;
}