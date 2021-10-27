#pragma once
#include "CBattleship.h"

class CGridPiece
{
public:
	enum class EState { UNCHECKED, FRIENDLY, FRIENDLYHIT, HIT, EMPTY, ENEMY };
	CGridPiece();
	CGridPiece(CGridPiece::EState PieceState, CBattleship* PieceOwner);

private:
	EState State;
	CBattleship* Owner;
public:
	EState GetState() { return State; }
	CBattleship* GetOwner() { return Owner; }

	void SetState(EState PieceState) { State = PieceState;  }
	void SetOwner(CBattleship* PieceOwner) { Owner = PieceOwner; }
};

