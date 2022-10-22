/***********************************************************************
* Header File:
*    Rook
* Author:
*		Ashley DeMott, Logan Huston
* Summary:
*		A rook in chess. This file contains info on drawing a rook.
************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.h"
#endif

class Rook : public Piece
{
public:
	// Call Piece's constructor
   Rook(RC position, bool isWhite) : Piece(position, isWhite) 
   {
      this->type = 'r'; // Rook type
      this->rectangles =
      {
         {-8,7,  -8,4,  -4,4,  -4,7},   // left battlement
         { 8,7,   8,4,   4,4,   4,7},   // right battlement
         { 2,7,   2,4,  -2,4,  -2,7},   // center battlement
         { 4,3,   4,-5, -4,-5, -4,3},   // wall
         { 6,-6, -6,-6, -6,-8,  6,-8}   // base
      };
   }
   set <Move> getPossibleMoves(Board* board);
};