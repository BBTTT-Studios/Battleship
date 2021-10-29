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
			default:
				std::cout << "?";
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
			Piece = GetGridValue(ship->GetShipLocation().row, ship->GetShipLocation().col + i);
			break;

		case CBattleship::ERotationDirection::DOWN:
			Piece = GetGridValue(ship->GetShipLocation().row - i, ship->GetShipLocation().col);
			break;

		case CBattleship::ERotationDirection::LEFT:
			Piece = GetGridValue(ship->GetShipLocation().row, ship->GetShipLocation().col - i);
			break;

		case CBattleship::ERotationDirection::UP:
			Piece = GetGridValue(ship->GetShipLocation().row + i, ship->GetShipLocation().col);
			break;
		}
		Piece->SetState(isEnemy ? CGridPiece::EState::ENEMY : CGridPiece::EState::FRIENDLY);
		Piece->SetOwner(ship);
		
	}
	DrawGrid();
}

void CGrid::MoveShip(CBattleship* ship, int row, int col)
{
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			CGridPiece* piece = GetGridValue(r+1, c+1 );
			if (piece->GetOwner() == ship)
			{
				piece->SetState(CGridPiece::EState::UNCHECKED);
				piece->SetOwner(nullptr);
			}
		}
	}
	
	//TODO Add validation to keep player inside the grid
	//TODO Prevent ship placement on top of other ships
	//TODO Prevent grid units from being overwritten and reset when a ship is moved over them
	ship->SetShipLocation(row, col);
	DrawGrid();
}
