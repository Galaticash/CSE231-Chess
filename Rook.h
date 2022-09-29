/***********************************************************************
 * Header File:
 *    Rook:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	// Call the base Constructor
	Rook(RC position, bool isWhite) : Piece()
	{};
	set <Move> getPossibleMoves(Piece* board[]) { set <Move> possible; return possible; };
};