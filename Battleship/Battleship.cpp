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
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool continueGame = true;
bool setUp = true;

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

//TODO Two Grids; one to place our ships on, one to guess for enemy ships
int main()
{
    CGrid grid;
    char xlet;
	int xloc;
    int yloc;

	CBattleship* ship = new CBattleship(CBattleship::EShipType::BATTLESHIP, CBattleship::ERotationDirection::RIGHT, 1, 1);

	//CBattleship ship2 = CBattleship(CBattleship::EShipType::DESTROYER, CBattleship::ERotationDirection::DOWN, 4, 2);
	//grid.PlaceShip(&ship2, true);

	while (setUp)
	{

		int c = 0;
		grid.PlaceShip(ship, false);
		switch((c=_getch()))
		{
		case KEY_LEFT:
			grid.MoveShip(ship, ship->GetShipLocation().row, ship->GetShipLocation().col-1);
			break;
		
		case KEY_RIGHT:
			grid.MoveShip(ship, ship->GetShipLocation().row, ship->GetShipLocation().col+1);
			break;
		
		case KEY_UP:
			grid.MoveShip(ship,ship->GetShipLocation().row-1, ship->GetShipLocation().col);
			break;
		
		case KEY_DOWN:
			grid.MoveShip(ship,ship->GetShipLocation().row+1, ship->GetShipLocation().col);
			break;
		default:
			std::cout << "Def";
		}
		//grid.DrawGrid();
		
	}
	
    while (continueGame)
    {
        std::cout << "Row: ";
		validateInput(xlet);
		if (xlet >= 97) { xloc = xlet - 96; }
		else if (xlet >= 65) { xloc = xlet - 64; }

        std::cout << "Col: ";
		validateInput(yloc);

        grid.CheckLocation(xloc, yloc);


    }
    
}
