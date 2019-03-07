#include <iostream>
#include "tinyxml.h"
#include "CD.h"
#include <vector>


int next() {
    std::vector<CD> lijstje_ffs;

    TiXmlDocument doc;
    if (!doc.LoadFile("../test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }


    for (TiXmlElement *elemm = root->FirstChildElement(); elemm != NULL;
         elemm = elemm->NextSiblingElement()) {
        std::string artist;
        std::string title;
        std::string year;
        double price = 0;
        bool error = false;

        for (TiXmlElement *elem = elemm->FirstChildElement(); elem != NULL;
             elem = elem->NextSiblingElement()) {

            if (elem->GetText() != nullptr) {


                std::string elemName = elem->Value();

                if (elemName == "TITLE") {
                    title = elem->GetText();
                } else if (elemName == "ARTIST") {
                    artist = elem->GetText();
                } else if (elemName == "PRICE") {
                    try {
                        price = std::stod(std::string(elem->GetText()));
                    } catch (std::invalid_argument &e) {
                        std::cout << "prijs is geen double!" << std::endl;
                        error = true;
                        break;
                    }

                } else if (elemName == "YEAR") {
                    year = elem->GetText();
                }
            } else {
                std::cout << "lege tag!" << std::endl;
                error = true;
                break;
            }


        }
        if (not error) {
            lijstje_ffs.emplace_back(CD(artist, title, year, price));
            lijstje_ffs[lijstje_ffs.size() - 1].print_cd();
        }

    }
    doc.Clear();
    return 0;
}


int test() {
    return next();
}