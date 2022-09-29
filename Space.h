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
	Space()
	{
		this->currentPosition = RC(-1, -1);
		this->isWhite = false;
	};
	Space(RC position, bool isWhite = 0) : Piece()
	{
		this->type = "SPACE";
	};
	set <Move> getPossibleMoves(Piece* board[], Move lastMove) { set <Move> possible; return possible; };
};