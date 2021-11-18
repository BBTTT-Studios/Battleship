/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CGridPiece.h
Description : Class that holds information about each position on the game board
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/


#pragma once
#include "CBattleship.h"

class CGridPiece
{
public:
	enum class EState { UNCHECKED, FRIENDLY, FRIENDLYHIT, HIT, EMPTY, ENEMY, OVERLAPPING };
	CGridPiece();
	CGridPiece(EState pieceState, CBattleship* pieceOwner);

	struct Coords
	{
		int Row;
		int Col;
	};

private:
	EState State_m;
	EState OldState_m;
	CBattleship* OldOwner_m;
	CBattleship* Owner_m;
	//Coords Position_m;
	
public:
	EState GetState() const { return State_m; }
	CBattleship* GetOwner() const { return Owner_m; }

	void SetState(const EState pieceState) { OldState_m = State_m; State_m = pieceState;  }
	void RevertState() { State_m = OldState_m; }
	void SetOwner(CBattleship* pieceOwner) { OldOwner_m = Owner_m; Owner_m = pieceOwner; }

};

