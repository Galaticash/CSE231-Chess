/***********************************************************************
 * Header File:
 *    Rook:
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

class Rook : public Piece
{
public:
	// Call the base Constructor
   Rook(RC position, bool isWhite) : Piece(position, isWhite) 
   {
      this->type = 'r';
   }

   set <Move> getPossibleMoves(Board* board, Move lastMove);
};