#include "CBattleship.h"




CBattleship::CBattleship(const EShipType type = EShipType::BATTLESHIP, const ERotationDirection rotation = ERotationDirection::RIGHT, const int row = 1, const int col = 1):
	ShipLength_m(0)
{
	ShipRotation_m = rotation;
	ShipType_m = type;
	ShipLocation_m = Coords{row, col};

	switch (ShipType_m)
	{
	case EShipType::CRUISER:
		ShipLength_m = 3;
		break;
	case EShipType::BATTLESHIP:
		ShipLength_m = 4;
		break;
	case EShipType::SUBMARINE:
		ShipLength_m = 4;
		break;
	case EShipType::DESTROYER:
		ShipLength_m = 2;
		break;
	case EShipType::CARRIER:
		ShipLength_m = 5;
		break;
	}

	ShipHealth_m = ShipLength_m;
}

CBattleship::~CBattleship()
{

}


void CBattleship::SetShipLocation(const int row, const int col)
{

		ShipLocation_m.Col = col;
		ShipLocation_m.Row = row;

}


