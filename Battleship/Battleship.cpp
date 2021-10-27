// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CGrid.h"
#include <sstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include "CBattleship.h"

using std::string; using std::vector;
using std::cout; using std::endl;
using std::cin; using std::numeric_limits;

bool continueGame = true;

template<typename T>
T& validateInput(T& val)
{
	while (true) {
		if (cin >> val) {
			break;
		}
		else {
			cout << "Enter a valid value!\n";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return val;
}


int main()
{
    CGrid grid;
    char xlet;
	int xloc;
    int yloc;


	CBattleship ship = CBattleship(CBattleship::EShipType::BATTLESHIP, CBattleship::ERotationDirection::RIGHT, 1, 1);
	grid.PlaceShip(&ship, true);

	CBattleship ship2 = CBattleship(CBattleship::EShipType::DESTROYER, CBattleship::ERotationDirection::DOWN, 4, 2);
	grid.PlaceShip(&ship2, true);

    while (continueGame)
    {
        std::cout << "Row: ";
		validateInput(xlet);
		if ((int)xlet >= 97) { xloc = (int)xlet - 96; }
		else if ((int)xlet >= 65) { xloc = (int)xlet - 64; }

        std::cout << "Col: ";
		validateInput(yloc);

        grid.CheckLocation(xloc, yloc);


    }
    
}
