/***********************************************************************
* Header File:
*    Pawn
* Author: 
*		Ashley DeMott, Logan Huston
* Summary: 
*		A pawn in chess. This file contains info on drawing a pawn.
************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.h"
#endif

class Pawn : public Piece
{
public:
	// Call Piece's constructor
	Pawn(RC position, bool isWhite) : Piece(position, isWhite)
	{
		this->type = 'p';	// Pawn type
		this->rectangles = {
			{ 1,7,  -1,7,  -2,5,  2,5 }, // top of head
			{ 3,5,  -3,5,  -3,3,  3,3 }, // bottom of head
			{ 1,3,  -1,3,  -2,-3, 2,-3}, // neck
			{ 4,-3, -4,-3, -4,-5, 4,-5}  // base
		};
	};
	set <Move> getPossibleMoves(Board* board);
};