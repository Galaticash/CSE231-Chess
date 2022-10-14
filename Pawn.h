/***********************************************************************
 * Header File:
 *    Pawn:
 * Author: 
 *
 * Summary: 
 *
 ************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.cpp"
#endif

class Pawn : public Piece
{
public:
	// Call the base Constructor
	Pawn(RC position, bool isWhite) : Piece(position, isWhite)
	{
		this->type = 'p';
		this->rectangles = {
			{ 1,7,  -1,7,  -2,5,  2,5 }, // top of head
			{ 3,5,  -3,5,  -3,3,  3,3 }, // bottom of head
			{ 1,3,  -1,3,  -2,-3, 2,-3}, // neck
			{ 4,-3, -4,-3, -4,-5, 4,-5}  // base
		};
	};

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};