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
	Space(RC position, bool isWhite = 0) : Piece()
	{};
	set <Move> getPossibleMoves(Piece* board[]) { set <Move> possible; return possible; };
};