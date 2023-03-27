#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace  std;

#include "Ship.h"
#include "BattlefieldGrid.h"
#include "FiringGrid.h"

void InsertComputerShips(BattlefieldGrid& grid);
string RandomCoordinate();

int main() {
    int playerShips;
    int computerShips;
    string fileName;
    vector<char> player;
    string ready;
    string type;
    string coordinate;
    string direction;
    int count = 1;
    bool errorCheck;
    int randNum;
    string computerCoordinate;
    char value;
    string playerCoordinate;
    char tmp;
    bool prove;

    // Initialize the battlefield grids for both the player and computer
    BattlefieldGrid grids = BattlefieldGrid();

    cout << "In this game of Battleship, you will enter ships through the ship_placement.csv file \n"
            "and then you will enter the coordinates where you think that the enemy's ships are. \n"
            "If the shot is a miss, then an X will be placed on the grid and if the shot is a hit, \n"
            "then an O will be placed on the grid." << endl << endl;
    cout << "If you would like to change the layout of your ships, please change them in the \n"
            "ship_placement.csv file." << endl << endl;
    cout << "Enter any key to continue or enter q to quit." << endl;
    cin >> ready;

    if (ready == "q") {
        return 0;
    }

    try {
        ifstream shipFile;
        shipFile.open("../ship_placement.csv");

        if (!shipFile.is_open()) {
            cout << "Could not open ship_placement.csv" << endl;
        } else {
            // The loop continues until there is nothing left or all of the 5 ships have already been gone through.
            while (!shipFile.fail() && count <= 5) {
                getline(shipFile, type, ',');
                getline(shipFile, coordinate, ',');
                getline(shipFile, direction, '\n');
                Ship placeShip = Ship(type, coordinate, direction, count);
                // Pass the Battlefield player vector by reference into the ship SetPosition function
                errorCheck = grids.SetPlayerBattlefield(placeShip);

                if (!errorCheck) {
                    throw runtime_error ("Invalid coordinate or direction.");
                }
                count++;
            }
            cout << endl;

            shipFile.close();
            grids.OutputPlayerGrid();
        }
    } catch (runtime_error& excpt) {
        cout << excpt.what() << endl;
        cout << "Please check the ship_placement.csv file and enter a valid coordinate or direction." << endl;
        return 0;
    }catch (...) {
        cout << "There was an error opening the file!" << endl;
        return 0;
    }

    // Set up the ships for the computer
    InsertComputerShips(grids);

    // Initialize the firing grids
    FiringGrid firing = FiringGrid();
    // The amount of ships is initially 5
    computerShips = 5;
    playerShips = 5;

    // Determine who will go first by selecting a random num between 0 and 1
    srand(time(0));
    randNum = rand() % 2;

    if (randNum == 0) {
        cout << "Your enemy will fire at your ships first." << endl;
        // Computer fires at a random coordinate
        computerCoordinate = RandomCoordinate();
        value = grids.CheckPosition(computerCoordinate, "computer");
        if (value == ' ') {
            // set the given coordinate on the firing grid to be 'X' for a miss.
            firing.SetMissedCoordinate(computerCoordinate, "computer");
            //firing.OutputComputerFiringGrid();
        } else {
            // A ship has been hit and the firing gid will be set to 'O' at the coordinate. Also sink the player ship
            firing.SetHitCoordinate(value, "computer", grids);
            grids.SinkPlayerShip(value);
            playerShips--;
            cout << "The enemy sank one of your ships!" << endl;
        }
    } else {
        cout << "You will fire at your enemy's ships first." << endl;
    }

    cin.ignore();
    // while there are still ships continue asking for a position to fire at
    while (computerShips != 0 && playerShips != 0) {
        prove = false;
        // prove must be true in order for the player to continue. The player must enter a valid coordinate.
        while (!prove) {
            try {
                // Ask for position to fire at
                cout
                        << "Enter the coordinate where you want to fire at. Enter the column (A-J) and then the row (1-10) \n"
                           "without anything in between them. Example: A1. Enter q to quit" << endl;
                getline(cin, playerCoordinate);

                if (playerCoordinate == "q") {
                    return 0;
                }

                tmp = playerCoordinate[0];
                if (tmp != 'A' && tmp != 'B' && tmp != 'C' && tmp != 'D' && tmp != 'E' && tmp != 'F' && tmp != 'G' &&
                    tmp != 'H' && tmp != 'I' && tmp != 'J') {
                    throw runtime_error("Invalid column input.");
                } else {
                    prove = true;
                }
            } catch (runtime_error &excpt) {
                cout << excpt.what() << endl;
                cout << "Please put in the correct coordinate." << endl;
            }
        }

        // Gets the coordinate at the given position and stores it in value.
        value = grids.CheckPosition(playerCoordinate, "player");
        if (value == ' ') {
            // set the given coordinate on the firing grid to be 'X' for a miss.
            firing.SetMissedCoordinate(playerCoordinate, "player");
        } else {
            // A ship has been hit and the firing gid will be set to 'O' at the coordinate. Also sink the computer ship
            firing.SetHitCoordinate(value, "player", grids);
            grids.SinkComputerShip(value);
            computerShips--;
            cout << "Good job! You sank one of the enemy ships." << endl;
        }

        // Computer fires at a random coordinate
        computerCoordinate = RandomCoordinate();
        value = grids.CheckPosition(computerCoordinate, "computer");
        if (value == ' ') {
            // set the given coordinate on the firing grid to be 'X' for a miss.
            firing.SetMissedCoordinate(computerCoordinate, "computer");
        } else {
            // A ship has been hit and the firing gid will be set to 'O' at the coordinate. Also sink the player ship
            firing.SetHitCoordinate(value, "computer", grids);
            grids.SinkPlayerShip(value);
            playerShips--;
            cout << "The enemy sank one of your ships!" << endl;
        }

        // Display a summary of the remaining ships and the player's battlefield and firing grids.
        cout << "You have " << playerShips << " ships remaining. Your enemy has " << computerShips << " ships remaining." << endl;
        grids.OutputPlayerGrid();
        firing.OutputPlayerFiringGrid();
    }

    // The game has ended. If the ships that the player has left is 0, that means that they lost and the computer wins.
    if (playerShips == 0) {
        cout << "The enemy has sunken all of your ships. You lose." << endl;
    } else {
        cout << "You sank all of the enemy ships. You win!" << endl;
    }

    // At the end of the game, I should print the opponent's battlefield grid
    grids.OutputComputerGrid();
    firing.OutputComputerFiringGrid();
    grids.OutputPlayerGrid();
    firing.OutputPlayerFiringGrid();

    return 0;
}

// Generates a random setup of ships to put on the computer's battlefield grid.
void InsertComputerShips(BattlefieldGrid& grid) {
    string coordinate;
    string direction;
    string type;
    int randNum;
    vector<vector<char>> computerGrid;

    // This allows for different random numbers to be generated every time the program is run.
    srand(time(0));

    // Have 6 different preset options that will randomly be selected from
    randNum = rand() % 6;

    if (randNum == 0) {
        Ship carrier = Ship("Carrier", "A1", "VD", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "D3", "HR", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "H9", "VU", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "J2", "VD", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "C8", "HR", 5);
        grid.SetComputerBattlefield(destroyer);
    } else if (randNum == 1) {
        Ship carrier = Ship("Carrier", "D2", "HR", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "J7", "VU", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "B5", "HR", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "G7", "VD", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "B9", "VU", 5);
        grid.SetComputerBattlefield(destroyer);
    } else if (randNum == 2) {
        Ship carrier = Ship("Carrier", "J9", "HL", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "I5", "VU", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "A5", "VD", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "D4", "VD", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "B10", "HR", 5);
        grid.SetComputerBattlefield(destroyer);
    } else if (randNum == 3) {
        Ship carrier = Ship("Carrier", "A4", "VD", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "F1", "HR", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "D5", "VU", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "I5", "VD", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "E8", "HR", 5);
        grid.SetComputerBattlefield(destroyer);
    } else if (randNum == 4) {
        Ship carrier = Ship("Carrier", "J9", "HL", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "C6", "VD", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "E5", "VD", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "G2", "VD", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "B3", "HR", 5);
        grid.SetComputerBattlefield(destroyer);
    } else {
        Ship carrier = Ship("Carrier", "C6", "VU", 1);
        grid.SetComputerBattlefield(carrier);
        Ship battleship = Ship("Battleship", "B9", "HR", 2);
        grid.SetComputerBattlefield(battleship);
        Ship cruiser = Ship("Cruiser", "E5", "HR", 3);
        grid.SetComputerBattlefield(cruiser);
        Ship submarine = Ship("Submarine", "H4", "VU", 4);
        grid.SetComputerBattlefield(submarine);
        Ship destroyer = Ship("Destroyer", "I8", "VD", 5);
        grid.SetComputerBattlefield(destroyer);
    }

}

// Generates a random coordinate for the computer when it is firing at the player battlefield grid.
string RandomCoordinate() {
    int randRow;
    int randColumn;
    char column;
    string computerCoordinate;

    srand(time(0));

    randRow = (rand() % 10) + 1;
    randColumn = (rand() % 10) + 1;
    column = char(randColumn + 64);
    computerCoordinate = column + to_string(randRow);

    return computerCoordinate;
}