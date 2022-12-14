/***********************************************************************
 * Header File:
 *    Knight:
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

class Knight : public Piece
{
public:
	// Call the base Constructor
	Knight(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'n';
		this->rectangles = {
      {-7,3,  -3,6,  -1,3,  -5,0},  // muzzle
      {-2,6,  -2,8,   0,8,   0,3},  // head
      {-3,6,   3,6,   6,1,   1,1},  // main
      { 6,1,   1,1,  -5,-5,  5,-5}, // body
      { 6,-6, -6,-6, -6,-8,  6,-8}  // base
        };
    };
	
   set <Move> getPossibleMoves(Board* board, Move lastMove);
};