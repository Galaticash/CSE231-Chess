/***********************************************************************
 * Header File:
 *    King:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	// Call the base Constructor
	King(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'k';
    };

	set <Move> getPossibleMoves(Piece* board[][8][8], Move lastMove);
};