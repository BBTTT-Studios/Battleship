#include "CBattleship.h"

CBattleship::CBattleship(EShipType Type = EShipType::BATTLESHIP, ERotationDirection Rotation = ERotationDirection::RIGHT, int row = 1, int col = 1)
{
	ShipRotation = Rotation;
	ShipType = Type;
	ShipLocation = Coords{ row, col };

	switch (ShipType)
	{
	case EShipType::CRUISER:
		ShipLength = 3;
		break;
	case EShipType::BATTLESHIP:
		ShipLength = 4;
		break;
	case EShipType::SUBMARINE:
		ShipLength = 4;
		break;
	case EShipType::DESTROYER:
		ShipLength = 2;
		break;
	case EShipType::CARRIER:
		ShipLength = 5;
		break;
	}

	ShipHealth = ShipLength;

}

CBattleship::~CBattleship()
{

}