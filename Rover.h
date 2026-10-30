//
// Created by William Wright on 10/28/26.
//

#ifndef CSCI1300_CS1_ROVER_H
#define CSCI1300_CS1_ROVER_H
#include "Direction.h"
#include "Location.h"
#include "Mission.h"
#include "World.h"


class Rover {
private:
    static const char COMMAND_FORWARD = 'F';
    static const char COMMAND_LEFT = 'L';
    static const char COMMAND_RIGHT = 'R';
    static const char COMMAND_SCAN = 'S';
    static const char COMMAND_CHARGE = 'C';
    static const int MOVE_COST = 2;
    static const int TURN_COST = 1;
    static const int SCAN_COST = 3;
    static const int FULL_CHARGE = 100;

    Location location;
    Direction heading;
    int batteryLevel;
    World world;

    string directionToString(Direction direction);
    bool isAtLocation(Location& position);
    void setPosition(Location next);

    bool turnLeft();
    bool turnRight();
    bool goForward();
    bool charge();
    bool scan();

    bool executeCommand(char command);
    void printCommandStatus(char command, bool wasSuccessful);

public:
    Rover(Location initialLocation, Direction initialHeading, int initialBatteryLevel);

    void putOnWorld(World mars);
    string toString();

    void executeMission(Mission &mission);
};

#endif //CSCI1300_CS1_ROVER_H
