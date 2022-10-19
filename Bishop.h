/***********************************************************************
 * Header File:
 *    Bishop
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A bishop in chess. This file contains info on drawing a bishop.
 ************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.h"
#endif

class Bishop : public Piece
{
public:
	// Call the base Constructor
	Bishop(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'b';
		this->rectangles = {
      {-1,8,  -1,2,   1,2,   1,8 },   // center of head
      { 1,8,   1,2,   5,2,   5,5 },   // right part of head
      {-4,5,  -4,2,  -2,2,  -2, 6},   // left of head
      {-5,3,  -5,2,   5,2,   5,3 },   // base of head
      {-2,2,  -4,-5,  4,-5,  2,2 },   // neck
      { 6,-6, -6,-6, -6,-8,  6,-8}    // base
        };
    };

	set <Move> getPossibleMoves(Board* board);
};