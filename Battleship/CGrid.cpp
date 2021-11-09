
#include "CGrid.h"
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "termcolor.hpp"


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
	std::cout << termcolor::white << "  1 2 3 4 5 6 7 8 9 10" << termcolor::reset << std::endl;
	for (int row = 0; row < 10; row++)
	{
		std::cout << static_cast<char>(65 + row);
		for (int col = 0; col < 10; col++)
		{
			//GridArray_m[row][col].SetPosition(row, col);
			switch (GridArray_m[row][col].GetState())
			{
			case CGridPiece::EState::UNCHECKED:
				std::cout << termcolor::bright_blue << " ." << termcolor::reset;
				break;

			case CGridPiece::EState::ENEMY:
				std::cout << termcolor::bright_blue << " ." << termcolor::reset;
				break;

			case CGridPiece::EState::HIT:
				std::cout << termcolor::red << " X" << termcolor::reset;
				break;

			case CGridPiece::EState::FRIENDLYHIT:
				std::cout << termcolor::red << " X" << termcolor::reset;
				break;

			case CGridPiece::EState::EMPTY:
				std::cout << termcolor::yellow << " O" << termcolor::reset;
				break;

			case CGridPiece::EState::FRIENDLY:
				std::cout << termcolor::green << " F" << termcolor::reset;
				break;

			case CGridPiece::EState::OVERLAPPING:
				std::cout << termcolor::italic << " F" << termcolor::reset;
				break;
				
			default:
				std::cout << termcolor::bright_blue << "?" << termcolor::reset;
			}
		}
		
		std::cout << std::endl;
		
	}
	std::cout << std::endl;
}



void CGrid::CheckLocation(const int &row, const int &col)
{
	CGridPiece& gridPiece = GridArray_m[row - 1][col - 1];
	switch (gridPiece.GetState())
	{
	case CGridPiece::EState::ENEMY:
		gridPiece.SetState(CGridPiece::EState::HIT);
		gridPiece.GetOwner()->ReduceHealth();
		break;

	case CGridPiece::EState::FRIENDLY:
		gridPiece.SetState(CGridPiece::EState::HIT);
		gridPiece.GetOwner()->ReduceHealth();
		break;
		
	default:
		GridArray_m[row - 1][col - 1].SetState(CGridPiece::EState::EMPTY);
		break;
	}
	DrawGrid();
}



void CGrid::PlaceShip(CBattleship* ship, const bool isEnemy)
{
		std::vector<CGridPiece*> pieces = GetShipPieces(ship);
		for (int i = 0; i < pieces.size(); i++)
		{
			pieces[i]->SetState(isEnemy ? CGridPiece::EState::ENEMY : CGridPiece::EState::FRIENDLY);
			pieces[i]->SetOwner(ship);
		}
	
	DrawGrid();
}



std::vector<CGridPiece*> CGrid::GetShipPieces(const CBattleship* ship)
{
	
	std::vector<CGridPiece*> pieces;
	for (int i = 0; i < ship->GetShipLength(); i++)
	{
		
		switch (ship->GetRotation())
		{
		case CBattleship::ERotationDirection::RIGHT:
			pieces.push_back(GetGridValue(ship->GetShipLocation().Row, ship->GetShipLocation().Col + i));
			break;

		case CBattleship::ERotationDirection::DOWN:
			pieces.push_back(GetGridValue(ship->GetShipLocation().Row + i, ship->GetShipLocation().Col));
			break;

		case CBattleship::ERotationDirection::LEFT:
			pieces.push_back(GetGridValue(ship->GetShipLocation().Row, ship->GetShipLocation().Col - i));
			break;

		case CBattleship::ERotationDirection::UP:
			pieces.push_back(GetGridValue(ship->GetShipLocation().Row - i, ship->GetShipLocation().Col));
			break;
		}
	}
	return pieces;
}



void CGrid::MoveShip(CBattleship* ship, const int row, const int col)
{

	bool canMove = false;

	const std::vector<CGridPiece*>& shipParts = GetShipPieces(ship);

	
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
	
	if (CheckMovementValidity(row, col, ship))
	{
		ship->SetShipLocation(row, col);
	}
	
	DrawGrid();
}



bool CGrid::CheckMovementValidity(int row, int col, CBattleship* ship)
{
	bool canMove = false;
	int colTest = 0;
	int rowTest = 0;
	int len = ship->GetShipLength();
	for (int i = 0; i < len; i++)
	{
		
		switch (ship->GetRotation())
		{
		case CBattleship::ERotationDirection::RIGHT:
			colTest = col + i;
			rowTest = row;
			break;

		case CBattleship::ERotationDirection::DOWN:
			rowTest = row + i;
			colTest = col;
			break;

		case CBattleship::ERotationDirection::LEFT:
			colTest = col - i;
			rowTest = row;
			break;

		case CBattleship::ERotationDirection::UP:
			rowTest = row - i;
			colTest = col;
			break;
		}
		if ((colTest > 0 and colTest < 11) and (rowTest > 0 and rowTest < 11))
		{
			if (GetGridValue(rowTest, colTest)->GetOwner() == nullptr or GetGridValue(rowTest, colTest)->GetOwner() == ship )
			{
				canMove = true;
			}
			else
			{
				canMove = false;

				break;
			}
		}
		else
		{
			canMove = false;
			break;
		}
	}
	return canMove;
}



void CGrid::RotateShip(CBattleship* ship)
{
	CBattleship::ERotationDirection OldRotation = ship->GetRotation();
	switch (ship->GetRotation())
	{
	case CBattleship::ERotationDirection::RIGHT: ship->SetShipRotation(CBattleship::ERotationDirection::DOWN); break;
	case CBattleship::ERotationDirection::DOWN: ship->SetShipRotation(CBattleship::ERotationDirection::LEFT); break;
	case CBattleship::ERotationDirection::LEFT: ship->SetShipRotation(CBattleship::ERotationDirection::UP); break;
	case CBattleship::ERotationDirection::UP: ship->SetShipRotation(CBattleship::ERotationDirection::RIGHT); break;
	}
	if (!CheckMovementValidity(ship->GetShipLocation().Row, ship->GetShipLocation().Col, ship))
	{
		ship->SetShipRotation(OldRotation);
	}
}