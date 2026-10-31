//
// Created by William Wright on 10/28/26.
//
#include <iostream>
using namespace std;

#include "Location.h"
#include "Mission.h"

Mission::Mission(string theCommands) {
    commands = theCommands;
}

bool Mission::isQuit() {
    return commands == "quit";
}

string Mission::getStatus() {
    string status = "-----Mission Complete!-----\n";
    status += "Number of Successful Commands: " + to_string(numSuccessfulCommands) + "\n";
    if (goalReached) {
        status += "Goal reached!\n";
    }
    return status;
}

string Mission::getCommands() {
    return commands;
}

Location &Mission::getGoal() {
    return goal;
}

void Mission::setGoal(Location& newGoal) {
    goal = newGoal;
}

void Mission::setGoalReached(bool successOrFailure) {
    goalReached = successOrFailure;
}

void Mission::incrementSuccessfulCommandCount() {
    numSuccessfulCommands++;
}
