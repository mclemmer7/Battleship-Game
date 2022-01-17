#ifndef FINAL_PROJECT_SHIP_H
#define FINAL_PROJECT_SHIP_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ship {
private:
    // Create a vector to store the ships for both the player and computer
    string shipType;
    string shipCoordinate;
    string shipDirection;
    int size;
    int row;
    int column;
    char letter;
    int shipNum;
    char num;

public:
    // Constructor
    Ship(string type, string coordinate, string direction, int num);

    void SetSize();
    bool SetPosition(vector<vector<char>>& playerGrid);
};


#endif //FINAL_PROJECT_SHIP_H
