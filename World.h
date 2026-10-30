//
// Created by William Wright on 10/28/26.
//

#ifndef CSCI1300_CS1_WORLD_H
#define CSCI1300_CS1_WORLD_H

#include "Location.h"

class World {
    int width;
    int height;
    Location chargingStationLocation;

public:
    World();
    World(const int size, Location& chargerLoc);

    bool isOutOfBounds(Location& location);
    Location& getChargingStationLocation();
    int getMinCoord();
    int getMaxCoord();
};

#endif //CSCI1300_CS1_WORLD_H
