/***********************************************************************
 * Header File:
 *    King:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.cpp"
#endif


class King : public Piece
{
public:
	// Call the base Constructor
	King(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'k';
    };

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};