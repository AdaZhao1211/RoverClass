//
// Created by Bill Wright on 10/28/26.
//

#include <iostream>
using namespace std;

#include "Location.h"
#include "World.h"
#include "Direction.h"
#include "Mission.h"
#include "Rover.h"

Location getLocation(string prompt, int minCoord, int maxCoord) {
    int x, y;
    do {
        cout << prompt;
        cin >> x >> y;
    } while (x < minCoord || x > maxCoord || y < minCoord || y > maxCoord);

    return Location{x, y};
}

Mission getMission(int minCoord, int maxCoord) {
    cout << endl << "Input mission (type 'quit' to exit): ";
    string userEnteredMission;
    cin >> userEnteredMission;
    Mission mission(userEnteredMission);

    if (mission.isQuit()) {
        return mission;
    }

    Location goal = getLocation("Input goal as 'x y': ", minCoord, maxCoord);
    mission.setGoal(goal);
    return mission;
}

int main() {
    int WORLD_WIDTH = 10;
    int WORLD_HEIGHT = 10;
    Location chargerLocation{0, 0};
    World mars(WORLD_WIDTH, WORLD_HEIGHT, chargerLocation);

    Location startingLocation{0, 0};
    Rover rover(startingLocation, Direction::EAST, 40);
    rover.putOnWorld(mars);

    while (true) {
        Mission mission = getMission(mars.getMinCoord(), mars.getMaxCoord());
        if (mission.isQuit()) {
            break;
        }
        rover.executeMission(mission);
        cout << mission.getStatus();
        cout << "Rover ended at " << rover.toString() << endl;
    }
    return 0;
}