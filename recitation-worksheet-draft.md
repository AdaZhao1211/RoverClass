# Rover Mission Control: Multi-file Compilation and File I/O

CSCI 1300 • Recitation worksheet • Working draft

Names: ______________________________   Date: _______________

## Activity overview

You will turn an interactive rover program into a program that reads missions from a file and records the rover's output in another file. First, download and run the multi-file project and answer questions about how its files work together. Next, give the Rover an output stream while keeping keyboard input. Finally, read missions from missions.csv and show progress in the console. Test after each change.

By the end, you should be able to compile several C++ implementation files together, pass an output stream by reference, and open, read, and write files.

Work in pairs and switch driver after Part 3. Plan for about 50 minutes for Parts 1–4. Extra credit may take another 20–30 minutes, depending on your experience with parsing and validation.

## 1. Download, open, and run (7 minutes)

Download the supplied mutliFileRoverVersion starter folder and the supplied CSV files. Open the project folder in your editor. Keep the header and implementation files together.

Open a terminal in the project folder and compile all five implementation files:

```sh
g++ -std=c++11 mainProject.cpp Rover.cpp Mission.cpp World.cpp Location.cpp -o rover
./rover
```

On a fresh run, enter these two missions in order. Type each goal when prompted:

```text
Mission commands: FFLFS
Goal: 2 1
Mission commands: RFF
Goal: 4 1
Then enter: quit
```

Record the rover's final coordinates, heading, and battery. You will compare against this baseline after changing its input and output.

Baseline: ____________________________________________________

## 2. Answer some questions (8 minutes)

1. Which file contains main()? Where are the declaration and definition of the Rover constructor?
2. What belongs in Rover.h, and what belongs in Rover.cpp?
3. Why does including Rover.h not replace compiling Rover.cpp?
4. Predict what happens if you compile only mainProject.cpp. Try it with the command below. Is the failure a compiler syntax error or a linker error about missing definitions?
5. Locate the code that reads mission commands and goal coordinates. Locate the code that prints the result of each rover command. Which parts will you change for file input and file output?
6. After editing a .cpp file, what must you do before running the changed program?

```sh
g++ -std=c++11 mainProject.cpp -o rover_incomplete
```

Responses: __________________________________________________
_____________________________________________________________

## 3. Change cout into an output stream (20 minutes)

Keep reading mission commands and goals from the keyboard during this part.

### A. Give Rover an output stream

In Rover.h, include <ostream>. Add a private instance variable of type std::ostream& named output. Add a fourth constructor parameter, std::ostream& outputStream, to both the constructor declaration in Rover.h and its definition in Rover.cpp.

An ostream is an output stream: cout and an open ofstream can both be passed to this parameter. The & means the Rover refers to the existing stream instead of copying it.

Initialize the reference in the constructor's initializer list, before the constructor body:

```cpp
Rover::Rover(Location initialLocation, Direction initialHeading,
             int initialBatteryLevel, std::ostream& outputStream)
    : output(outputStream)
{
    // Keep the existing constructor body here.
}
```

A reference member must be initialized this way; assigning to it inside the constructor body is not a substitute.

### B. Send Rover's messages to the stream

Replace every cout in Rover.cpp with output, including command status messages, invalid-command messages, and charger messages. For example:

```cpp
output << "Command " << command << " ";
```

Keep the prompts in mainProject.cpp writing to cout so the user can see them.

### C. Open an output file in main()

Include <fstream> in mainProject.cpp. Before constructing the Rover, prompt for an output filename and open an output file stream using the pattern from lecture:

```cpp
string outputFileName;
cout << "Enter an output file name (no spaces): ";
cin >> outputFileName;

ofstream fout; // Declare an output file stream variable
fout.open(outputFileName); // Try to open the file

// Check if the file opened successfully
if (fout.fail()) {
    cout << "File couldn't be opened!" << endl;
    return -1; // Exit with error code
}
cout << "File opened successfully!" << endl;
```

Pass fout as the fourth argument when constructing the Rover:

```cpp
Rover rover(startingLocation, Direction::EAST, 100, fout);
```

Declare and open fout before constructing rover, and keep it open while the rover runs. Preserve the world setup and the keyboard-based mission loop. After each mission, also send main()'s mission summary and final rover state to fout:

```cpp
fout << mission.getStatus();
fout << "Rover ended at " << rover.toString() << endl;
```

Use a separate output filename, such as rover_keyboard_log.txt. Do not use either input CSV filename as your output filename.

### D. Verify keyboard input and file output

Recompile all five .cpp files. Run the program, choose rover_keyboard_log.txt, and repeat the two baseline missions from Part 1. Enter quit, then open the output file.

- The program still prompts for commands and goals in the console.
- The file contains the result of each rover command and both mission summaries.
- Final coordinates, heading, and battery match your baseline.
- A fresh run with the same output filename replaces the previous log by default.

What changed about where the output appears? __________________

## 4. Change cin into a file input stream (15 minutes)

Now replace the keyboard-based mission loop with a loop that reads missions from the supplied missions.csv. Keep the output filename prompt from Part 3. Mission commands and goals should no longer require keyboard entry.

The CSV has no header. Each line contains mission_commands, goal_x, goal_y. For this part, every line contains valid input:

```text
FFLFS,2,1
RFF,4,1
LLFFFF,0,1
```

The rover keeps its location, heading, and battery between missions. Create the Rover once, before the loop. End-of-file ends the mission loop; the CSV does not contain quit.

### A. Open the input file

Put missions.csv in the directory from which you run the program. Use the same declare, open, and fail-check pattern:

```cpp
ifstream fin; // Declare an input file stream variable
fin.open("missions.csv"); // Try to open the file

// Check if the file opened successfully
if (fin.fail()) {
    cout << "File couldn't be opened!" << endl;
    return -1; // Exit with error code
}
cout << "File opened successfully!" << endl;
```

### B. Read and execute one mission per line

Include <sstream>. Use getline(fin, line) as your loop condition so each iteration handles one CSV record. A stringstream lets you read fields from that line; getline with ',' as the delimiter separates the fields.

Complete this outline:

```cpp
string line;
int missionNumber = 0;
while (getline(fin, line)) {
    stringstream row(line);
    string commands, xText, yText;
    getline(row, commands, ',');
    getline(row, xText, ',');
    getline(row, yText);

    int goalX = stoi(xText);
    int goalY = stoi(yText);
    Mission mission(commands);
    Location goal{goalX, goalY};
    // Set the mission's goal.
    // Increase missionNumber.
    // Print a progress message to cout.
    // Execute the mission.
    // Print "done!" to cout.
    // Write the mission summary and final rover state to fout.
}
```

The supplied input is valid, so stoi can convert the coordinate strings to integers without additional validation in this part. Stop calling getMission() in the new loop; it prompts for keyboard input.

### C. Show progress in the console

Before executing each mission, print its number, commands, and goal to cout. Print done! after executeMission returns. For example:

```text
Mission 1: FFLFS with a goal of (2,1) running...done!
```

Use cout for these progress messages and fout for the mission summaries. Rover's detailed command output goes to its stored output stream. Here, done means execution finished; consult the log to see whether commands succeeded and the goal was reached.

### D. Verify the complete run

Recompile and run with rover_csv_log.txt as the output filename.

- The console shows three numbered progress messages, one for each CSV line.
- The program runs every mission without prompting for mission commands or goals.
- The log contains 14 command-result messages and three mission summaries.
- The first two missions match your keyboard test.
- The program finishes at end-of-file without creating an extra mission.
- Temporarily rename missions.csv and verify that the program reports the open failure. Restore the name afterward.

Record the final coordinates, heading, and battery: ____________
Explain why while (getline(fin, line)) is preferable to while (!fin.eof()): ____________________________________________________

## 5. Extra credit: Validate a messy mission file (20–30 additional minutes)

Read the supplied missions_garbage.csv. It mixes valid missions with invalid commands, missing fields, extra fields, non-integer coordinates, out-of-range coordinates, and a blank line.

Validate the entire record before creating and executing its mission. For this exercise:

- Require exactly three comma-separated fields. Trim surrounding whitespace.
- Require a nonempty command string containing only uppercase F, L, R, S, or C.
- Require two complete integer coordinate values. Reject text such as 2oops or 1.5; accepting only a numeric prefix is not enough.
- Require goal coordinates from 0 through 9 for the intended 10-by-10 world.
- Treat blank lines and missing fields as invalid records.
- Print each error to cout with the source line number and a useful reason, then continue to the next line.
- Do not execute any commands from an invalid record. Valid records after errors must still run.

Keep a source line counter separate from your executed-mission counter. Count blank and invalid lines in source line numbers. A fresh stringstream for each line keeps a parsing failure on one line from preventing later lines from being read.

If you use stoi, catch conversion and range errors and check how much of the string it consumed.

A valid mission can still have a command fail during execution, such as moving beyond the world's edge or charging away from the charger. Report that through the rover's normal output; it is different from a malformed CSV record.

Verification: the supplied file has valid missions on lines 1, 11, and 12. Report errors for lines 2–10, execute only those three valid missions, and verify that the final rover state matches Part 4.

## Instructor notes — remove before distributing

Supply the starter folder plus missions.csv and missions_garbage.csv. No download URL has been assigned in this draft.

Expected results for the valid file: mission 1 ends at (2, 1), NORTH, battery 90 with 5 successful commands; mission 2 ends at (4, 1), EAST, battery 85 with 3 successful commands; mission 3 ends at (0, 1), WEST, battery 75 with 6 successful commands. All three reach their goals.

The valid test file uses interior coordinates. The current starter has unrelated world issues: World assigns width from height, and Location::isWithinBounds excludes the maximum coordinate returned by World. Resolve these separately before testing edge coordinates in extra credit. The current charge() implementation already returns true when charging succeeds.

Parts 1–4 are a 50-minute target with the provided constructor and parsing scaffolds. If students are new to references or stringstream, allow more time; reserve robust validation for extra credit.
