//
// Created by William Wright on 10/28/26.
//

#ifndef CSCI1300_CS1_MISSION_H
#define CSCI1300_CS1_MISSION_H


class Mission {
    Location goal;
    string commands;
    bool goalReached = false;
    int numSuccessfulCommands = 0;

public:
    Mission(string theCommands);
    bool isQuit();
    string getStatus();
    string getCommands();
    Location& getGoal();
    void setGoal(Location& newGoal);
    void setGoalReached(bool successOrFailure);
    void incrementSuccessfulCommandCount();
};

#endif //CSCI1300_CS1_MISSION_H
