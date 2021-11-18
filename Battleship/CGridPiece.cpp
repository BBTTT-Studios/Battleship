/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CGridPiece.cpp
Description : Implementation of CGridPiece.h
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

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
