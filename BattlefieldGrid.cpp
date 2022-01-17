#include "BattlefieldGrid.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Initialize all of the characters in the 10 by 10 vector to a space ' '.
BattlefieldGrid::BattlefieldGrid() {
    // i is the row number
    for (int i = 0; i < 10; i++) {
        // j is the column number
        for (int j = 0; j < 10; j++) {
            playerRows.push_back(' ');
            computerRows.push_back(' ');
        }
        player.push_back(playerRows);
        computer.push_back(computerRows);
    }
}

// This will output the 10 by 10 grid showing either the battleships on the board or the firing grid.
void BattlefieldGrid::OutputGrid(vector<vector<char>> grid) {
    index = 0;

    cout << "     A   B   C   D   E   F   G   H   I   J" << endl << "   ";

    for (int k = 1; k <= 41; k++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 1; i <= 10; i++) {
        if (i == 10) {
            cout << i << " |";
        } else {
            cout << i << "  |";
        }

        // Output the elements from the given vector onto the grid
        for (int j = 0; j < 10; j++) {
            cout << " " << grid[i-1][j] << " |";
            index++;
        }
        cout << endl << "   ";
        for (int k = 1; k <= 41; k++) {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl;
}

// This will output the player grid.
void BattlefieldGrid::OutputPlayerGrid() {
    cout << "This is the layout of your battleships:" << endl;
    OutputGrid(player);
}

// This will output the computer grid.
void BattlefieldGrid::OutputComputerGrid() {
    cout << "This is the layout of your enemy's battleships:" << endl;
    OutputGrid(computer);
}

// Returns the battlefield grid of the player.
vector<vector<char>> BattlefieldGrid::GetPlayerGrid() {
    return player;
}

// Returns the battlefield grid of the computer.
vector<vector<char>> BattlefieldGrid::GetComputerGrid() {
    return computer;
}

// Returns true if the given position and direction are valid.
bool BattlefieldGrid::SetPlayerBattlefield(Ship playerShip) {
    return playerShip.SetPosition(player);
}

// Returns true if the given position and direction are valid.
void BattlefieldGrid::SetComputerBattlefield(Ship computerShip) {
    computerShip.SetPosition(computer);
}

// Returns the character at the given coordinate
char BattlefieldGrid::CheckPosition(string coordinate, string user) {
    // Convert the given row number from a string to an int.
    if (coordinate.length() == 3) {
        row = stoi(coordinate.substr(1,2));
    } else {
        row2 = coordinate[1];
        row = row2 - 48;
    }

    // Convert the column letter to an integer
    letter = coordinate[0];
    column = letter - 65;

    if (user == "player") {
        // check computer battlefield grid
        value = computer[row-1][column];
    } else {
        // check player battlefield grid
        value = player[row-1][column];
    }

    return value;
}

// Returns the number of ships that have not been sunk and sinks the player ship.
int BattlefieldGrid::SinkPlayerShip(char sinkValue) {
    // sink the player ship
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (player[i][j] == sinkValue) {
                player[i][j] = 'O';
            }
        }
    }

}

// Returns the number of ships that have not been sunk and sinks the computer ship.
int BattlefieldGrid::SinkComputerShip(char sinkValue) {
    // sink the computer ship
    // row i and column j
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (computer[i][j] == sinkValue) {
                computer[i][j] = 'O';
            }
        }
    }
}