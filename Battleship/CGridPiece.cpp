#include "CGridPiece.h"

CGridPiece::CGridPiece()
{
	State = EState::UNCHECKED;
	Owner = nullptr;
}

CGridPiece::CGridPiece(CGridPiece::EState PieceState, CBattleship* PieceOwner)
{
	State = PieceState;
	Owner = PieceOwner;
}
