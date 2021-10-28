#pragma once
#include "CBattleship.h"
#include "CGridPiece.h"

class CGrid
{
public:
	CGrid();
	~CGrid();

	void DrawGrid();
	void CheckLocation(const int &row, const int &col);
	enum class HitState { Unchecked, Miss, Hit };

private:
	
	CGridPiece gridArray[10][10];


public:
	CGridPiece* GetGridValue(int row, int col) 
	{ 
		CGridPiece* ptr;
		ptr = &gridArray[row - 1][col - 1];
		return ptr; 
	}
	

	void PlaceShip(CBattleship* ship, bool isEnemy);
	void MoveShip(CBattleship* ship, int row, int col);
};

