//
// Created by Bill Wright on 10/28/26.
//

#include <iostream>
#include <fstream>
#include <string> // EDIT
using namespace std;

#include "Location.h"
#include "World.h"
#include "Direction.h"
#include "Mission.h"
#include "Rover.h"

// EDIT to add to the handout
int split(string line, char delimiter, string fields[], int capacity) {
    if (capacity <= 0) {
        return -1;
    }

    int count = 0;
    string field;
    for (char character : line) {
        if (character == delimiter) {
            if (count >= capacity) {
                return -1;
            }
            fields[count++] = field;
            field = "";
        } else {
            field += character;
        }
    }

    if (count >= capacity) {
        return -1;
    }
    fields[count++] = field; // Include the final field, even if it is empty.
    return count;
}

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
    int WORLD_SIZE = 10;
    Location chargerLocation{0, 0};
    World mars(WORLD_SIZE, chargerLocation);

    Location startingLocation{0, 0};

    ifstream fin;
    fin.open("missions.csv");
    if (fin.fail()) {
        cout << "Input file couldn't be opened!" << endl;
        return -1;
    }

    // output
    string outputFileName;
    cout << "Enter an output file name: ";
    cin >> outputFileName;

    ofstream myfile;
    myfile.open(outputFileName); 
    if (myfile.fail()) {
        cout << "Output file couldn't be opened!" << endl;
        return -1;
    }
    // BILL: use cout as ostream first, test with it and then change ostream with ofstream

    // EDIT: Keep cout for the terminal demo; change only cout to myfile for file output.
    Rover rover(startingLocation, Direction::EAST, 40, myfile);
    rover.putOnWorld(mars);

    int missionNumber = 0;
    string line;
    while (getline(fin, line)) {
        string fields[3];
        int fieldCount = split(line, ',', fields, 3);
        if (fieldCount != 3) {
            cout << "Invalid mission format: " << line << endl;
            continue;
        }
        string command = fields[0];
        int goalX = stoi(fields[1]);
        int goalY = stoi(fields[2]);

        
        Mission mission(command);
        Location goal{goalX, goalY};
        mission.setGoal(goal);
        cout << "Mission " << ++missionNumber << ": " << command
             << " with a goal of (" << goalX << "," << goalY << ") running...";
        rover.executeMission(mission);
        cout << "done!" << endl;
        // myfile << mission.getStatus();
        // myfile << "Rover ended at " << rover.toString() << endl;
    }
    return 0;
}
