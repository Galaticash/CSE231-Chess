/***********************************************************************
 * Header File:
 *    Bishop: A bishop in chess
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the code for how a bishop is drawn.
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
		this->rectangles = {
      {-1,8,  -1,2,   1,2,   1,8 },   // center of head
      { 1,8,   1,2,   5,2,   5,5 },   // right part of head
      {-4,5,  -4,2,  -2,2,  -2, 6},   // left of head
      {-5,3,  -5,2,   5,2,   5,3 },   // base of head
      {-2,2,  -4,-5,  4,-5,  2,2 },   // neck
      { 6,-6, -6,-6, -6,-8,  6,-8}    // base
    };

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};