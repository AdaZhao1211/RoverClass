//
// Created by William Wright on 10/28/26.
//

#ifndef CSCI1300_CS1_LOCATION_H
#define CSCI1300_CS1_LOCATION_H
#include <string>
using namespace std;

class Location {
    int x = 0;
    int y = 0;

public:
    Location();
    Location(int x_pos, int y_pos);

    void add(Location& other);
    void incX();
    void decX();
    void incY();
    void decY();
    bool equals(Location &other);
    string toString();
    bool isWithinBounds(int minCoord, int maxCoord);

    int getX();
    int getY();
};

#endif //CSCI1300_CS1_LOCATION_H
