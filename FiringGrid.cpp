#include "FiringGrid.h"
#include <iostream>
#include <string>
using namespace std;

// If the a ship is hit, it is marked with an O. If it is a miss, it is marked with an X.
// It only takes one hit to sink a battleship, and all of the coordinates of the ship will have to be marked with O's.

// Default constructor for FiringGrid. Initializes the firing grids to a space for both the player and computer.
FiringGrid::FiringGrid() {
    // i is the row number
    for (int i = 0; i < 10; i++) {
        // j is the column number
        for (int j = 0; j < 10; j++) {
            rowsPlayer.push_back(' ');
            rowsComputer.push_back(' ');
        }
        playerFiring.push_back(rowsPlayer);
        computerFiring.push_back(rowsComputer);
    }
}

// Outputs the firing grid for the computer. Uses the OutputGrid function from BattlefieldGrid.
void FiringGrid::OutputComputerFiringGrid() {
    cout << "This is your enemy's firing grid:" << endl;
    OutputGrid(computerFiring);
}

// Outputs the firing grid for the player. Uses the OutputGrid function from BattlefieldGrid.
void FiringGrid::OutputPlayerFiringGrid() {
    cout << "This is your firing grid:" << endl;
    OutputGrid(playerFiring);
}

// Stores 'X' in the firing grid if the player or computer missed a ship.
void FiringGrid::SetMissedCoordinate(string coordinate, string user) {
    // Convert the given row number from a string to an int.
    row = stoi(coordinate.substr(1,2));
    // Convert the column letter to an integer
    letter = coordinate[0];
    column = letter - 65;

    // Convert the given row number from a string to an int.
    row = stoi(coordinate.substr(1, 2));
    // Convert the column letter to an integer
    letter = coordinate[0];
    column = letter - 65;
    if (user == "player") {
        playerFiring[row - 1][column] = 'X';
    } else {
        computerFiring[row - 1][column] = 'X';
    }
}

// Stores 'O' in the firing grid if the player or computer hit a ship.
void FiringGrid::SetHitCoordinate(char sinkValue, string user, BattlefieldGrid grids) {
    if (user == "computer") {
        playerBattlefield = grids.GetPlayerGrid();

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (playerBattlefield[i][j] == sinkValue) {
                    computerFiring[i][j] = 'O';
                }
            }
        }
    } else {
        computerBattlefield = grids.GetComputerGrid();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (computerBattlefield[i][j] == sinkValue) {
                    playerFiring[i][j] = 'O';
                }
            }
        }
    }
}