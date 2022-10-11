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
		  this->rectangles = 
        {
            { 1,8,  -1,8,  -1,1,   1,1},     // cross vertical
            {-3,6,   3,6,   3,4,  -3,4},     // cross horizontal
            {-8,3,  -8,-3, -3,-3, -3,3},     // bug bump left
            { 8,3,   8,-3,  3,-3,  3,3},     // bug bump right
            { 5,1,   5,-5, -5,-5, -5,1},     // center column
            { 8,-4, -8,-4, -8,-5,  8,-5},    // base center
            { 8,-6, -8,-6, -8,-8,  8,-8}     // base
		  };
    };

	set <Move> getPossibleMoves(Board* board, Move lastMove);
};