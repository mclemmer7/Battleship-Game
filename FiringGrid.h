#ifndef FINAL_PROJECT_FIRINGGRID_H
#define FINAL_PROJECT_FIRINGGRID_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "BattlefieldGrid.h"

// The FiringGrid class is a derived class of the BattlefieldGrid base class
class FiringGrid : public BattlefieldGrid {
private:
    vector<vector<char>> playerFiring;
    vector<char> rowsPlayer;
    vector<vector<char>> computerFiring;
    vector<char> rowsComputer;
    int row;
    char letter;
    int column;
    vector<vector<char>> playerBattlefield;
    vector<vector<char>> computerBattlefield;
public:
    FiringGrid();
    void OutputPlayerFiringGrid();
    void OutputComputerFiringGrid();
    void SetMissedCoordinate(string coordinate, string user);
    void SetHitCoordinate(char sinkValue, string user, BattlefieldGrid grids);
};


#endif //FINAL_PROJECT_FIRINGGRID_H
