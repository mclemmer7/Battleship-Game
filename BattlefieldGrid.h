#ifndef FINAL_PROJECT_BATTLEFIELDGRID_H
#define FINAL_PROJECT_BATTLEFIELDGRID_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Ship.h"


class BattlefieldGrid {
private:
    vector<vector<char>> player;
    vector<char> playerRows;
    vector<vector<char>> computer;
    vector<char> computerRows;
    int index;
    int row;
    int column;
    char letter;
    char value;
    char row2;


public:
    BattlefieldGrid();

    vector<vector<char>> GetPlayerGrid();
    vector<vector<char>> GetComputerGrid();

    bool SetPlayerBattlefield(Ship playerShip);
    void SetComputerBattlefield(Ship computerShip);

    void OutputPlayerGrid();
    void OutputComputerGrid();
    void OutputGrid(vector<vector<char>> grid);

    int SinkPlayerShip(char sinkValue);
    int SinkComputerShip(char sinkValue);
    char CheckPosition(string coordinate, string user);

};


#endif //FINAL_PROJECT_BATTLEFIELDGRID_H

