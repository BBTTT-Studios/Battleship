#pragma once
class CBattleship
{
public:
	enum class ERotationDirection { LEFT, RIGHT, UP, DOWN };
	enum class EShipType { BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, CARRIER };
	struct Coords { int row; int col; };

	CBattleship(EShipType, ERotationDirection, int x, int y);
	~CBattleship();

	


private:
	int ShipLength;
	int ShipHealth;
	Coords ShipLocation;
	EShipType ShipType;
	ERotationDirection ShipRotation;

public:
	int GetShipLength() { return ShipLength; }
	EShipType GetShipType() { return ShipType; }
	ERotationDirection GetRotation() { return ShipRotation; }
	Coords GetShipLocation() { return ShipLocation;  }

	void SetShipLocation(int row, int col);
	void SetShipRotation(EShipType Direction);
	void ReduceHealth() { ShipHealth--; }
};

