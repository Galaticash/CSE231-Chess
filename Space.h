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
		this->type = "SPACE";
	};
	Space(RC position, bool isWhite = 0) : Piece(position, isWhite)
	{
		this->type = "SPACE";
	};
	set <Move> getPossibleMoves(Piece* board[], Move lastMove) { set <Move> possible; return possible; };
};