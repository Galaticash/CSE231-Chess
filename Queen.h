/***********************************************************************
 * Header File:
 *    Queen:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	// Call the base Constructor
	Queen(RC position, bool isWhite) : Piece(position, isWhite)
    {
        this->type = 'q';
    };

   set <Move> getPossibleMoves(Piece* board[], Move lastMove);
};