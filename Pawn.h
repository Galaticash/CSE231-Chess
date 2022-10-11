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
	};

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};