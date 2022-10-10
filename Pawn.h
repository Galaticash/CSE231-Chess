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

// TODO: Add capture checks for Move class

class Pawn : public Piece
{
public:
	// Call the base Constructor
	Pawn(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'p';
    };

   set <Move> getPossibleMoves(Piece* board[][8][8], Move lastMove);
};