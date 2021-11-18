// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#define NOMINMAX

#include "CGrid.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "CBattleship.h"
#include "CGameManager.h"
#include "termcolor.hpp"


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
CGameManager GameManager;

bool continueGame = true;
bool setUp = true;
CGrid p1Grid;
CGrid p2Grid;
CBattleship *p1ShipList[5];
CBattleship *p2ShipList[5];

//Function Declarations
void PhasePlacing();
void PhaseGame();
void DrawGrids();

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
		DrawGrids();
		std::cout << "Row: ";
		ValidateInput(xlet);
		if (xlet >= 97) { xloc = xlet - 96; }
		else if (xlet >= 65) { xloc = xlet - 64; }

		std::cout << "Col: ";
		ValidateInput(yloc);

		p2Grid.CheckLocation(xloc, yloc);

		DrawGrids();
		cout << termcolor::red << "Enemy is thinking..." << termcolor::reset << endl;
		Sleep(1000);
		srand(time(NULL));
		p1Grid.GuessRandom();
		DrawGrids();

	}
	
}

//First phase of the game. Handles the play area initialization, when the player places all of their ships
void PhasePlacing()
{
	for (int i = 0; i < 5; i++)
	{
		bool placing = true;


		//TODO REMEMBER TO DELETE THE ALLOCATED MEMORY
		p1ShipList[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 1, 1);
		
		p2ShipList[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 5, 5);
		
		
		while (placing)
		{
			p1Grid.PlaceShip(p1ShipList[i], false);
			
			DrawGrids();
			std::cout << "Move: Arrow Keys   |   Rotate: R   |   Confirm: Enter" << endl;
			const int c = _getch();
			if (c && c != 224)
			{
				switch (c)
				{
				case KEY_ENTER:
					placing = false;
					break;

				case KEY_R:
					p1Grid.RotateShip(p1ShipList[i]);
					p1Grid.MoveShip(p1ShipList[i], p1ShipList[i]->GetShipLocation().Row, p1ShipList[i]->GetShipLocation().Col);
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
					p1Grid.MoveShip(p1ShipList[i], p1ShipList[i]->GetShipLocation().Row, p1ShipList[i]->GetShipLocation().Col-1);
					break;
					
				case KEY_RIGHT:
					p1Grid.MoveShip(p1ShipList[i], p1ShipList[i]->GetShipLocation().Row, p1ShipList[i]->GetShipLocation().Col+1);
					break;
					
				case KEY_UP:
					p1Grid.MoveShip(p1ShipList[i],p1ShipList[i]->GetShipLocation().Row-1, p1ShipList[i]->GetShipLocation().Col);
					break;
					
				case KEY_DOWN:
					p1Grid.MoveShip(p1ShipList[i],p1ShipList[i]->GetShipLocation().Row+1, p1ShipList[i]->GetShipLocation().Col);
					break;
					
				default:
					std::cout << "?";
					break;
				}
			}

			
			DrawGrids();
		}
		std::cout << endl << termcolor::red << "Enemy is thinking..." << termcolor::reset << endl;
		Sleep((100));
		p2Grid.PlaceShipRandom(p2ShipList[i], true);
	}
}

template<typename T>
static T& ValidateInput(T& val)
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


void DrawGrids()
{
	system("cls");
	cout << termcolor::yellow << "Your Ships:" << termcolor::reset << endl << endl;
	p1Grid.DrawGrid();

	cout << termcolor::yellow << "Enemy Waters:" << termcolor::reset << endl << endl;
	p2Grid.DrawGrid();
	
}

