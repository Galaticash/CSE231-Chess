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
	King(RC position, bool isWhite) : Piece()
	{};
	set <Move> getPossibleMoves(Piece* board[]) { set <Move> possible; return possible; };
};