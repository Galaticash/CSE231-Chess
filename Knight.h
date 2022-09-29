/***********************************************************************
 * Header File:
 *    Knight:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	// Call the base Constructor
	Knight(RC position, bool isWhite) : Piece()
	{};
	set <Move> getPossibleMoves(Piece* board[]) { set <Move> possible; return possible; };

};