/***********************************************************************
 * Header File:
 *    Pawn:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"
#include "Space.h" // check for empty position

// TODO: Add capture checks for Move class

class Pawn : public Piece
{
public:
	// Call the base Constructor
	Pawn(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = "PAWN";
    };

   set <Move> getPossibleMoves(Piece* board[], Move lastMove);
};