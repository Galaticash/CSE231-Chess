/***********************************************************************
 * Header File:
 *    Space
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A space on the chess board. This file sets what type of piece 
 *		it is and that it has no moves.
 ************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.cpp"
#endif

class Space : public Piece
{

public:
	Space() : Piece()
	{
		this->type = 's';
	};
	Space(RC position, bool isWhite = 0) : Piece(position, isWhite)
	{
		this->type = 's';
	};
	set <Move> getPossibleMoves(Board* board) { return set <Move> {}; };
};