/***********************************************************************
 * Header File:
 *    Knight
 * Author:
 *		Ashley DeMott, Logan Huston
 * Summary:
 *		A knight in chess. This file contains info on drawing a knight.
 ************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.h"
#endif

class Knight : public Piece
{
public:
	// Call Piece's constructor
	Knight(RC position, bool isWhite) : Piece(position, isWhite)
	{
        this->type = 'n';   // Knight type
		this->rectangles = {
      {-7,3,  -3,6,  -1,3,  -5,0},  // muzzle
      {-2,6,  -2,8,   0,8,   0,3},  // head
      {-3,6,   3,6,   6,1,   1,1},  // main
      { 6,1,   1,1,  -5,-5,  5,-5}, // body
      { 6,-6, -6,-6, -6,-8,  6,-8}  // base
        };
    };	
   set <Move> getPossibleMoves(Board* board);
};