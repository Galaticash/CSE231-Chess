/***********************************************************************
 * Header File:
 *    Bishop:
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

class Bishop : public Piece
{
public:
	// Call the base Constructor
	Bishop(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'b';
    };

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};