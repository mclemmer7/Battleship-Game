#include "Ship.h"
#include <vector>
#include <string>
using namespace std;

// Parametrized constructor for a ship.
Ship::Ship(string type, string coordinate, string direction, int num) {
    shipType = type;
    shipCoordinate = coordinate;
    shipDirection = direction;
    shipNum = num;
    SetSize();
}

// Sets the size of the ships based on their ship type.
void Ship::SetSize() {
    if (shipType == "Carrier") {
        size = 5;
    } else if (shipType == "Battleship") {
        size = 4;
    } else if (shipType == "Cruiser") {
        size = 3;
    } else if (shipType == "Submarine") {
        size = 3;
    } else if (shipType == "Destroyer") {
        size = 2;
    }
}

// Sets the position of the ships. Returns true if the given position and direction are valid.
bool Ship::SetPosition(vector<vector<char>>& grid) {
    row = stoi(shipCoordinate.substr(1,2));

    // Convert the column letter to an integer
    letter = shipCoordinate[0];
    column = letter - 65;

    // Convert shipNum to a character
    num = char(48+shipNum);

    // Check the given direction for the ship and then add it to the vector grid based on the direction
    if (shipDirection == "HL") {
        // Positioned horizontally to the left
        for (int i = 0; i < size; i++) {
            // Subtract 1 from the row since row is the number of the row, but not the index of the vector
            if (grid[row-1][column-i] == ' ') {
                grid[row - 1][column - i] = num;
            } else {
                return false;
            }
        }
        return true;
    } else if (shipDirection == "HR") {
        // Positioned horizontally to the right
        for (int i = 0; i < size; i++) {
            if (grid[row-1][column+i] == ' ') {
                grid[row - 1][column + i] = num;
            } else {
                return false;
            }
        }
        return true;
    } else if (shipDirection == "VD") {
        // Positioned vertically downwards
        for (int i = 0; i < size; i++) {
            if (grid[row-1+i][column] == ' ') {
                grid[row - 1 + i][column] = num;
            } else {
                return false;
            }
        }
        return true;
    } else if (shipDirection == "VU") {
        // Positioned vertically upwards
        for (int i = 0; i < size; i++) {
            if (grid[row-1-i][column] == ' ') {
                grid[row - 1 - i][column] = num;
            } else {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}