//
// Created by William Wright on 10/28/26.
//

#include "Location.h"

Location::Location() {
    x = 0;
    y = 0;
}

Location::Location(int xPos, int yPos) {
    x = xPos;
    y = yPos;
};

void Location::add(Location& other) {
    x += other.x;
    y += other.y;
}

void Location::incX() {
    x++;
}

void Location::decX() {
    x--;
}

void Location::incY() {
    y++;
}

void Location::decY() {
    y--;
}

bool Location::equals( Location& other) {
    return x == other.x && y == other.y;
}

string Location::toString() {
    return "(" + to_string(x) + ", " + to_string(y) + ")";
}

bool Location::isWithinBounds(int minCoord, int maxCoord) {
    return x >= minCoord && x <= maxCoord && y >= minCoord && y <= maxCoord;
}

int Location::getX() {
    return x;
}

int Location::getY() {
    return y;
}
