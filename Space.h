/***********************************************************************
 * Header File:
 *    Space:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

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
	set <Move> getPossibleMoves(Piece** board[], Move lastMove) { set <Move> possible; return possible; };
};