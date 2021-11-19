/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CGrid.h
Description : Represents the game board. Handles rendering, queries and player movement
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

#pragma once

#include "CBattleship.h"
#include "CGridPiece.h"


#include <vector>


class CGrid		// TF: Class
{
public:
	CGrid();
	~CGrid();

	//Refreshes the grid in the console
	void DrawGrid();

	// Queries a position on the grid and changes the state if it hits an enemy/friend. Then refreshes the grid
	bool CheckLocation(const int &row, const int &col);

	
private:
	//This is the game board array. All piece info is stored here
	CGridPiece GridArray_m[10][10];		// TF: Array


public:
	
	//Returns the grid piece at the specified coordinated
	CGridPiece* GetGridValue(const int row, const int col) 
	{
		CGridPiece* ptr = &GridArray_m[row - 1][col - 1];	// TF: Pointer Initialized
		return ptr; 
	}

	//Places a ship at the current cursor coordinates
	void PlaceShip(CBattleship* ship, bool isEnemy);

	void PlaceShipRandom(CBattleship* ship, bool isEnemy);

	bool GuessRandom();
	
	//Move a ship to a specified location, checking movement validity, and then running PlaceShip
	bool MoveShip(CBattleship* ship, int row, int col);

	//Returns true if the movement of the ship to the specified coordinates would be valid (no collision, completely inside the game board)
	bool CheckMovementValidity(int row, int col, CBattleship* ship);
	void RotateShip(CBattleship* ship);

	//Returns an array of grid pieces owned by the specified ship
	std::vector<CGridPiece*> GetShipPieces(const CBattleship* ship);
};

