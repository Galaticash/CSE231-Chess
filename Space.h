/***********************************************************************
 * Header File:
 *    Space: An empty space in chess
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		Inherits from the piece class and has a type that is accesible 
 *		to the board for comparisons.
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
	set <Move> getPossibleMoves(Board* board, Move lastMove) { set <Move> possible; return possible; };
};