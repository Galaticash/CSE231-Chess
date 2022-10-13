/***********************************************************************
 * Header File:
 *    Queen: A queen in chess
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the code for how a queen is drawn.
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
        this->rectangles  = 
        {
            Rect( 8,8,   5,8,   5,5,   8,5 ),     // right crown jewel
            Rect( -8,8,  -5,8,  -5,5,  -8,5 ),     // left crown jewel
            Rect( 2,8,  -2,8,  -2,5,   2,5 ),     // center crown jewel
            Rect( 7,5,   5,5,   1,0,   5,0 ),     // right crown holder
            Rect( -7, 5, -5, 5, -1, 0, -5, 0 ),     // left crown holder
            Rect( 1,5,   1,0,  -1,0,  -1,5 ),     // center crown holder
            Rect( 4,0,  -4,0,  -4,-2,  4,-2),     // upper base
            Rect( 6,-3, -6,-3, -6,-5,  6,-5),     // middle base
            Rect( 8,-6, -8,-6, -8,-8,  8,-8)      // base
        };
    };

   set <Move> getPossibleMoves(Board* board, Move lastMove);
};