//
// Created by Bill Wright on 10/28/26.
//

#include <iostream>
#include<fstream>
#include <string>

using namespace std;

#include "Location.h"
#include "World.h"
#include "Direction.h"
#include "Mission.h"
#include "Rover.h"

// split helper function
void split(string line, char delimiter, string fields[], int capacity) {
    if (capacity <= 0) {
        return;
    }

    int count = 0;
    string field;
    for (char character : line) {
        if (character == delimiter) {
            if (count >= capacity) {
                return;
            }
            fields[count++] = field;
            field = "";
        } else {
            field += character;
        }
    }

    if (count >= capacity) {
        return;
    }
    fields[count++] = field;
    return;
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

    string inputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    ifstream fin;
    fin.open(inputFilename);
    if (fin.fail()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    ofstream fout;
    string outputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;
    fout.open(outputFilename);
    if(fout.fail()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    Rover rover(startingLocation, Direction::EAST, 40, fout);
    rover.putOnWorld(mars);

    string line;
    while (getline(fin, line)) {
        // EDIT: Exactly two commas means exactly three fields.
        int commas = 0;
        for (char character : line) {
            if (character == ',') {
                commas++;
            }
        }
        if (commas != 2) {
            continue;
        }

        string fields[3];

        split (line, ',', fields, 3);

        // EDIT: Require at least one command and allow only F, L, R, S, or C.
        if (fields[0].empty()) {
            continue;
        }
        bool validCommands = true;
        for (char command : fields[0]) {
            if (command != 'F' && command != 'L' && command != 'R' &&
                command != 'S' && command != 'C') {
                validCommands = false;
                break;
            }
        }
        if (!validCommands) {
            continue;
        }

        // EDIT: Each coordinate must be exactly one digit from 0 to 9.
        if (fields[1].length() != 1 || fields[1][0] < '0' || fields[1][0] > '9' ||
            fields[2].length() != 1 || fields[2][0] < '0' || fields[2][0] > '9') {
            continue;
        }

        Mission mission (fields[0]);
        Location newGoal {stoi(fields[1]), stoi(fields[2])};
        mission.setGoal(newGoal);
        rover.executeMission(mission);
        cout << mission.getStatus();
        cout << "Rover ended at " << rover.toString() << endl;
    }
    return 0;
}
