#include "CGrid.h"
#include <iostream>

CGrid::CGrid()
{
	std::cout << "Grid Initialized" << std::endl;
	DrawGrid();

}

CGrid::~CGrid()
{

}

void CGrid::DrawGrid()
{
	system("CLS");
	std::cout << "  1 2 3 4 5 6 7 8 9 10" << std::endl;
	for (int row = 0; row < 10; row++)
	{
		std::cout << char(65 + row);
		for (int col = 0; col < 10; col++)
		{
			switch (gridArray[row][col].GetState())
			{
			case CGridPiece::EState::UNCHECKED:
				std::cout << " .";
				break;

			case CGridPiece::EState::ENEMY:
				std::cout << " .";
				break;

			case CGridPiece::EState::HIT:
				std::cout << " X";
				break;

			case CGridPiece::EState::EMPTY:
				std::cout << " O";
				break;

			case CGridPiece::EState::FRIENDLY:
				std::cout << " F";
				break;
			}
		}
		
		std::cout << std::endl;
		
	}
	std::cout << std::endl;
}

void CGrid::CheckLocation(const int &row, const int &col)
{
	CGridPiece& GridPiece = gridArray[row - 1][col - 1];
	switch (GridPiece.GetState())
	{
	case CGridPiece::EState::ENEMY:
		GridPiece.SetState(CGridPiece::EState::HIT);
		GridPiece.GetOwner()->ReduceHealth();
		break;

	default:
		gridArray[row - 1][col - 1].SetState(CGridPiece::EState::EMPTY);
		break;
	}
	DrawGrid();
}

void CGrid::PlaceShip(CBattleship* ship, bool isEnemy)
{
	for (int i = 0; i < ship->GetShipLength(); i++)
	{
		CGridPiece* Piece = nullptr;
		switch (ship->GetRotation())
		{
		case CBattleship::ERotationDirection::RIGHT:
			Piece = GetGridValue(ship->GetShipLocation().x, ship->GetShipLocation().y + i);
			break;

		case CBattleship::ERotationDirection::DOWN:
			Piece = GetGridValue(ship->GetShipLocation().x - i, ship->GetShipLocation().y);
			break;

		case CBattleship::ERotationDirection::LEFT:
			Piece = GetGridValue(ship->GetShipLocation().x, ship->GetShipLocation().y - i);
			break;

		case CBattleship::ERotationDirection::UP:
			Piece = GetGridValue(ship->GetShipLocation().x + i, ship->GetShipLocation().y);
			break;
		}
		Piece->SetState(isEnemy ? CGridPiece::EState::ENEMY : CGridPiece::EState::FRIENDLY);
		Piece->SetOwner(ship);
		
	}
	DrawGrid();
}