#include "CGridPiece.h"

CGridPiece::CGridPiece()
{
	State_m = EState::UNCHECKED;
	Owner_m = nullptr;
}

CGridPiece::CGridPiece(const EState pieceState, CBattleship* pieceOwner)
{
	State_m = pieceState;
	Owner_m = pieceOwner;
}
