/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CBattleship.h
Description : Holds information about each ship in the game
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

#pragma once

class CBattleship
{
public:
	enum class ERotationDirection { LEFT, RIGHT, UP, DOWN };
	enum class EShipType { DESTROYER, CRUISER, SUBMARINE, BATTLESHIP, CARRIER };
	struct Coords { int Row; int Col; };

	CBattleship(EShipType, ERotationDirection, int row, int col);
	CBattleship(const CBattleship &old);
	~CBattleship();

	


private:	// TF: Access Specifier
	int ShipLength_m;
	int ShipHealth_m;
	Coords ShipLocation_m;
	EShipType ShipType_m;
	ERotationDirection ShipRotation_m;
	//bool CheckInBounds(int row, int col);
	//bool CheckCollision(int row, int col);

public:
	int GetShipLength() const { return ShipLength_m; }
	EShipType GetShipType() const { return ShipType_m; }
	ERotationDirection GetRotation() const { return ShipRotation_m; }
	Coords GetShipLocation() const { return ShipLocation_m;  }

	void SetShipLocation(int row, int col);
	void SetShipRotation(ERotationDirection direction) { ShipRotation_m = direction; }
	void ReduceHealth() { ShipHealth_m--; }
};

