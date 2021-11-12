// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CGrid.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <vector>
#include <conio.h>
#include "CBattleship.h"

using std::string; using std::vector;
using std::cout; using std::endl;
using std::cin; using std::numeric_limits;

//Keypress definitions
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_R 114 

//Global variable initialization
bool continueGame = true;
bool setUp = true;
CGrid grid;
CBattleship *shipList[10];

//Function Declarations
void PhasePlacing();
void PhaseGame();

template<typename T>
T& ValidateInput(T& val);


//TODO Two Grids; one to place our ships on, one to guess for enemy ships

//TODO Detect overlapping ships instead of blocking movement, and only block placement
//TODO Implement a game class to handle grid creation and game management, and abstract away code from main?
//TODO Implement game flow and 'AI' or Player 2
//


//MAIN GAME FUNCTION
int main()
{

    PhasePlacing();
	
	PhaseGame();
	
	
}


//Handle the main game loop and keep track of win condition
void PhaseGame()
{
	char xlet;
	int xloc;
	int yloc;
	
	while (continueGame)
	{
		std::cout << "Row: ";
		ValidateInput(xlet);
		if (xlet >= 97) { xloc = xlet - 96; }
		else if (xlet >= 65) { xloc = xlet - 64; }

		std::cout << "Col: ";
		ValidateInput(yloc);

		grid.CheckLocation(xloc, yloc);
		grid.DrawGrid();

	}
	
}

//First phase of the game. Handles the play area initialization, when the player places all of their ships
void PhasePlacing()
{
	for (int i = 0; i < 5; i++)
	{
		bool placing = true;


		//TODO REMEMBER TO DELETE THE ALLOCATED MEMORY
		shipList[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 1, 1);
		
		while (placing)
		{
			grid.PlaceShip(shipList[i], false);
			grid.DrawGrid();
			const int c = _getch();
			if (c && c != 224)
			{
				switch (c)
				{
				case KEY_ENTER:
					placing = false;
					break;

				case KEY_R:
					grid.RotateShip(shipList[i]);
					grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col);
					break;

				default:
					std::cout << "?";
					break;
				}
			}
			
			else
			{
				switch(_getch())
				{
				case KEY_LEFT:
					grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col-1);
					break;
					
				case KEY_RIGHT:
					grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col+1);
					break;
					
				case KEY_UP:
					grid.MoveShip(shipList[i],shipList[i]->GetShipLocation().Row-1, shipList[i]->GetShipLocation().Col);
					break;
					
				case KEY_DOWN:
					grid.MoveShip(shipList[i],shipList[i]->GetShipLocation().Row+1, shipList[i]->GetShipLocation().Col);
					break;
					
				default:
					std::cout << "?";
					break;
				}
			}
			grid.DrawGrid();
		}
	}
}

template<typename T>
T& ValidateInput(T& val)
{
	while (true) {
		if (!(cin >> val))
		{
			cout << "Enter a valid value!\n";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}
	return val;
}