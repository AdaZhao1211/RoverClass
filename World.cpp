//
// Created by William Wright on 10/28/26.
//

#include "Location.h"
#include "World.h"

World::World() {}

World::World(const int size, Location& chargerLoc) {
    width = size;
    height = size;
    chargingStationLocation = chargerLoc;
};

bool World::isOutOfBounds(Location& location) {
    return !location.isWithinBounds(getMinCoord(), getMaxCoord());
}

Location& World::getChargingStationLocation() {
    return chargingStationLocation;
}

int World::getMinCoord() {
    return 0;
}

int World::getMaxCoord() {
    return width - 1;
}

