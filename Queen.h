/***********************************************************************
 * Header File:
 *    Queen:
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


class Queen : public Piece
{
public:
	// Call the base Constructor
	Queen(RC position, bool isWhite) : Piece(position, isWhite)
    {
        this->type = 'q';
    };

   set <Move> getPossibleMoves(Board* board, Move lastMove);
};