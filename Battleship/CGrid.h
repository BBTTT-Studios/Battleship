#pragma once

#include "CBattleship.h"
#include "CGridPiece.h"


#include <vector>


class CGrid
{
public:
	CGrid();
	~CGrid();

	void DrawGrid();
	void CheckLocation(const int &row, const int &col);
	enum class HitState { UNCHECKED, MISS, HIT };

private:
	
	CGridPiece GridArray_m[10][10];


public:
	CGridPiece* GetGridValue(const int row, const int col) 
	{
		CGridPiece* ptr = &GridArray_m[row - 1][col - 1];
		return ptr; 
	}
	

	void PlaceShip(CBattleship* ship, bool isEnemy);
	void MoveShip(CBattleship* ship, int row, int col);
	bool CheckMovementValidity(int row, int col, CBattleship* ship);
	void RotateShip(CBattleship* ship);
	std::vector<CGridPiece*> GetShipPieces(const CBattleship* ship);
};

