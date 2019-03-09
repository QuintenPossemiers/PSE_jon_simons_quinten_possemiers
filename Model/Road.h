//
// Created by Quinten on 3/9/2019.
//

#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H


#include <string>
#include <vector>

class Road {

    /**section reserved for variables*/
private:
    std::string name;                    //Unique name
    unsigned int speed_limit, length;    //length of the road in meters
    std::vector<Road *> connections;     //Road you can get to by using this one

    /**section for getters and setters does not include add connection*/
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getSpeed_limit() const;

    void setSpeed_limit(unsigned int speed_limit);

    unsigned int getLength() const;

    const std::vector<Road *> &getConnections() const;

    /**constructor
     *
     * The constructor requires a name, length and speed limit connection are to be added via the designated function
     * */
public:
    Road(const std::string &name, unsigned int speed_limit, unsigned int length);

    /**section for overloading operators*/
public:
    bool operator==(const Road &rhs) const;

    bool operator!=(const Road &rhs) const;
};


#endif //UNTITLED_ROAD_H
