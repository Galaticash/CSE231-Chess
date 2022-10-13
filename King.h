/***********************************************************************
 * Header File:
 *    King: A king in chess
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the code for how a king is drawn.
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
		  this->rectangles = 
        {
            Rect(  1,8,  -1,8,  -1,1,   1,1),     // cross vertical
            Rect( -3,6,   3,6,   3,4,  -3,4),     // cross horizontal
            Rect( -8,3,  -8,-3, -3,-3, -3,3),     // bug bump left
            Rect( 8,3,   8,-3,  3,-3,  3,3),     // bug bump right
            Rect( 5,1,   5,-5, -5,-5, -5,1),     // center column
            Rect( 8,-4, -8,-4, -8,-5,  8,-5),    // base center
            Rect( 8,-6, -8,-6, -8,-8,  8,-8)     // base
		  };
    };

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};